#include "pedido.hpp"

// inicializamos nuestro atributo estatico 
int Pedido::n_pedidos_ = 0;

// Implementación del método observador estático
int Pedido::n_pedidos() noexcept {
    return n_pedidos_;
}

Pedido::Pedido(UsuarioPedido& UP, PedidoArticulo& PA, Usuario& u,
    const Tarjeta& t, const Fecha& f) : num_{n_pedidos_++}, tarjeta_{&t}, fecha_{f}, total_{0.0} {
        // si no hay articulos
        if (u.compra().empty()) throw Pedido::Vacio(&u);

        // si el usuario es otro al que realiza la compra
        if (t.titular() != &u) throw Pedido::Impostor(&u);

        // si la tarjeta esta caducada o desactivado, excepción
        if (t.caducidad() < fecha_) throw Pedido::Caducada(t.caducidad());
        if (!t.activa()) throw Pedido::Desactivada(t);

        // Vemos si queda stock de todos los articulos <Articulo*, size_t>
        for (Usuario::Articulos::const_iterator i = u.compra().begin(); i != u.compra().end(); i++){
            if((i.first)->stock() < i->second){ // vemos si la cantidad de articulos es superior al del su maximo
                u.vaciar_carro();
                throw Pedido::SinStock(i.first);
            }
        }

        // creamos las asociaciones existentes de clases
        UP.asocia(*this, u);

        for (Usuario::Articulos::const_iterator it = u.compra().begin(); i != u.compra().end(); i++){
            Articulo* A = it->first; // obtenemos el articulo correspondiente
            size_t cont = it->second; // obtenemos el numero de ejemplares del producto

            // obtenemos el precio de venta
            double pv_a = A->precio();

            // calculamos el precio total del producto
            total_ += pv_a * cont;

            // añadimos en enlace de pedido_articulo (pedido, articulo, precio venta ,cantidad)
            PA.pedir(*this, i.first, pv_a, cont); // pedir(Pedido&, Articulo&, double pv, size_t n)

            // actualizamos el stock de dicho articulo
            (i.first)->stock() -= i.second;
        }
    // vaciamos el carro del usuario
    u.vaciar_carro();
}

// falta operador de insercion de flujo
std::ostream& operator<<(std::ostream& os, const Pedido& p){
    os << "Nº Pedido: " << p.numero() << std::endl;
    os << "Fecha: " << p.fecha() << std::endl;
    os << "Tarjeta: " << p.tarjeta()->type() << "Nº:" << p.tarjeta()->numero() << std::endl;
    os << "Importe total: " << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl;
    return os;
};