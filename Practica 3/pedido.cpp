#include "pedido.hpp"

// inicializamos nuestro atributo estatico constante
int Pedido::n_pedidos = 0;

// Implementación del método observador estático
int Pedido::n_pedidos() noexcept {
    return n_pedidos_;
}

Pedido::Pedido(UsuarioPedido& UP, PedidoArticulo& PA, Usuario& u,
    const Tarjeta& t, const Fecha& f) : num_{n_pedidos_ + 1}, tarjeta_{&t}, fecha_{f}, total_{0.0} {
        // si no hay articulos
        if (u.compra().empty()) throw Pedido::Vacio(&u);

        // si el usuario es otro al que realiza la compra
        if (t.titular() != &u) throw Pedido::Impostor(&u);

        // si la tarjeta esta caducada o desactivado, excepción
        if (t.caducidad() < fecha_) throw Pedido::Caducada(t.caducidad());

        // Vemos si queda stock del articulo
        for (auto i : u.compra()){
            if((i.first)->stock() < i->second){ // vemos si la cantidad de articulos es superior al del su maximo
                u.vaciar_carro();
                throw Pedido::SinStock(i.first);
            }
        }

        // creamos las asociaciones existentes de clases

        // asociacion usuario-pedido
        UP.asocia(*this, u);

        for (auto& i: u.compra()){ // clave articulo, valor num prod
            // importe total = precio articulo * cantidad_producto
            total_ += i.first->precio() * i.second;

            // añadimos en enlace de pedido_articulo (pedido, articulo, precio venta ,cantidad)
            PA.pedir(*this, i.first, (i.first)->preio(), i.second);

            // actualizamos el stock de dicho articulo
            (i.first)->stock() -= i.second;
        }

        // Aumentamos el n_pedidos del usuario
        n_pedidos_++;
    }

// falta operador de insercion de flujo