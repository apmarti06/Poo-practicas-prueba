#include "articulo.hpp"
#include "pedido.hpp"
#include <map>
#include <algorithm>

#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

class PedidoArticulo {
    public:
        // Creamos los miembros públicos de los diccionarios de las clases de asociación (ordenación)
        struct OrdenaArticulos {
            bool operator() (const Articulo* A, const Articulo* B) const;
        };

        struct OrdenaPedidos {
            bool operator() (const Pedido* A, const Pedido* B) const;
        };

        // En map, se puede añadir tercer y cuarto argumento
        // Siendo el tercer argumento un comparador de ordenación, y el cuarto un asignador de memoria

        // asociacion directa 
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> Pedido_Articulo; // asoc directa

        // asociacion inversa
        typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
        typedef std::map<Articulo*, Pedidos, OrdenaArticulos> Articulo_Pedido; // asoc inversa

        // Creador de enlaces bidireccionales, indicando la cantidad por defecto si no se añade, + funcion sobrecargada invertida
        void pedir(const Pedido& p, const Articulo& a, double pv, unsigned int n = 1);
        void pedir(const Articulo&, const Pedido&, double, unsigned int n = 1); 
        
        // Funciones consultoras miembras publicas
        const ItemsPedido detalle(Pedido& P) const; // colección de articulos de un pedido, con su precio de venta y cantidad
        const Pedidos ventas(Articulo& A) const; // colección de pedidos de un articulo, con su precio de venta y cantidad

        // Metodos que imprimen detalles de todos los pedidos y ventas, de los dos contenedores
        std::ostream& mostrarDetallesPedidos(std::ostream& os) const;
        std::ostream& mostrarVentasArticulos(std::ostream& os) const;

        private:
            Pedido_Articulo directa; // el nombre directa es el contenedor de asoc de pedido_articulo
            Articulo_Pedido inversa; // e inversa es justo lo reverso a directa
};

// Operadores de flujo de insercion externos
std::ostream& operator <<(std::ostream& os, const PedidoArticulo::ItemsPedido& Itpe);
std::ostream& operator <<(std::ostream& os, const PedidoArticulo::Pedidos& Ped);

#endif