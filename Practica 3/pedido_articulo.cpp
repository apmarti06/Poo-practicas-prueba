#include "pedido_articulo.hpp"

// creamos todo tipo de iterador para buscar en diccionarios, nose si serian correctos
typedef PedidoArticulo::ItemsPedido::const_iterator IT;
typedef PedidoArticulo::Pedidos::const_iterator IP;

typedef PedidoArticulo::Pedido_Articulo::const_iterator ID;
typedef PedidoArticulo::Articulo_Pedido::const_iterator II;

bool PedidoArticulo::OrdenaArticulos::operator() (const Articulo* A, const Articulo* B){
    return (A->referencia() < B->referencia());
}

bool PedidoArticulo::OrdenaPedidos::operator() (const Pedido* A, const Pedido* B){
    return (A->numero() < B->numero());
}

void PedidoArticulo::pedir(const Pedido& p, const Articulo& a, double pv, unsigned int n = 1){
    // creamos en pedir el objeto linea de pedido para meterlo en el diccionario
    LineaPedido lp(pv, n);

    // creamos los enlaces de linea de venta directa e inversa, 
    //sin tener en cuenta que haya ocurrencias ya que estan ordenadas
    directa[&p].insert(std::make_pair(&a, lp)); // <Pedido*, map<Articulo*, LineaPedido, OrdenaArticulos>, OrdenaPedidos>
    inversa[&a].insert(std::make_pair(&p, lp)); // <Articulo*, map<Pedido*, LineaPedido, OrdenaPedidos>, OrdenaArticulos>
}

void PedidoArticulo::pedir(const Articulo& a, const Pedido& p, double pv, unsigned int n = 1){
    pedir(p, a, pv, n);
}

const PedidoArticulo::ItemsPedido PedidoArticulo::detalle(const Pedido& P) const{
    // buscamos el pedido, para ver si tiene asignado un articulo
    ID i = directa.find(&P);

    if(i != directa.end()){
        return i->second; // devolvemos el pedido si existe (ItemsPedido)
    } else {
        // si no existe devolvemos un pedido vacio
        PedidoArticulo::ItemsPedido pedido_vacio;
        return pedido_vacio;
    }
}

const PedidoArticulo::Pedidos PedidoArticulo::ventas(const Articulo& A) const{
    // buscamos el articulo, para ver si esta asignado a un pedido
    II i = inversa.find(&A);
    
    if(i != inversa.end()){
        return i->second; // devolvemos el pedido si existe
    } else {
        PedidoArticulo::Pedidos ventas_vacias;
        return ventas_vacias;
    }
}

// Detalles pedido e importe total
std::ostream& operator<<(std::ostream& os, const PedidoArticulo::ItemsPedido& IP){
    double total = 0.0; // almacenamos de un pedido el total

    os << "PVP\t Cantidad\t Articulo" << std::endl 
    << std::setw(65) << std::setfill('=') << ' ' << std::endl;

    // insertamos los datos del pedido
    for (const PedidoArticulo::ItemsPedido& i : IP){
        total += i.second.precio_venta() * i.second.cantidad(); // ajustamos a dos decimales la precion de double
        os << std::fixed << std::setprecision(2) << i.second.precio_venta()
        << "$" << i.second.cantidad() << "\t" << "[" << i.first->referencia() << // first recordar que se crea con un puntero 
        "] \"" << i.first->titulo() << "\"" << std::endl;
    }

    os << std::setw(65) << std::setfill('=') << ' ' << std::endl <<
    "Total" << std::fixed << std::setprecision(2) << total << "$" << std::endl;

    return os;
}

// Mostrar detalles como precio, cantidad, fecha de un pedido
std::ostream& operator<<(std::ostream& os, const PedidoArticulo::Pedidos& pedidos){
    // variables locales total y n ejemplares
    double total = 0.0;
    unsigned n = 0;
    // Mostramos todos los pedidos
    os << "[Pedidos:" << pedidos.size() << "]\n" << std::setw(65) <<
    std::setfill('=') << ' ' << std::endl;

    os << "PVP\t Cantidad\t Fecha de venta" << std::endl << std::setw(65) <<
    std::setfill('=') << ' ' << std::endl;

    for (const PedidoArticulo::Pedidos& i: pedidos){
        total += i.second.precio_venta() * i.second.cantidad(); // ajustamos a dos decimales la precion de double
        n++;
        os << i.second.precio_venta() <<" $\t" <<i.second.cantidad() 
        << "\t" << i.first->fecha() << std::endl;
    }

    os << std::setw(65) << std::setfill('=') << ' ' << std::endl 
        << std::fixed << std::setprecision(2) << total << "$\t" 
        << n << std::endl;

    return os;
}

// Operadores mostrar de clase asociacion, haciendo uso de los operadores creados ventas, y detalles para que no haya problemas de conversion

//  imprimirá en el flujo de salida proporcionado el detalle de todos los pedidos
std::ostream& PedidoArticulo::mostrarDetallesPedidos(std::ostream& os) const{
    // inicializamos las variables locales a usar
    double total = 0.0;
    unsigned npedido = 0;

    for (const PedidoArticulo::Pedido_Articulo& i : directa){ // i es el iterador de la clase asociacion directa, que contiene el pedido y el map de articulos
        npedido++;  `
        os << "\nPedido núm: " << npedido << std::endl << "Cliente:" << (*i.first)
        << detalle(*i.first) << std::endl; // llamamos al operador de flujo de insercion para mostrar el detalle del pedido
        total += i.first->total();
    }
    os << "Total Ventas\t " << std::fixed << std::setprecision(2) << total << "$ " << std::endl;

    return os;
}

// Aqui proporcionara todas las ventas agrupadas por articulos
std::ostream& PedidoArticulo::mostrarVentasArticulos(std::ostream& os) const{
    for (const PedidoArticulo::Articulo_Pedido& i : inversa){
        os << "Ventas de [" << (i.first)->referencia() << "]" <<
        (i.first)->titulo << " " << ventas(i.first) << std::endl; // llamamos al operador de flujo de insercion para mostrar el detalle del articulo 
    }
    return os;
}
