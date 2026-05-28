#include "articulo.hpp"
#include "pedido.hpp"

#ifndef LINEA_DE_PEDIDOS_HPP
#define LINEA_DE_PEDIDOS_HPP

// Haremos aqui la implementacion para la navegabilidad bidireccional de clases
class LineaPedido {
    public:
        // constructor evitando la conversion implicita
        explicit LineaPedido(double pv = 0.0, unsigned c = 1) : precio_venta_{pv}, cantidad_{c} {}

        // metodos consultoras
        inline double precio_venta() const noexcept { return precio_venta_; }
        inline unsigned cantidad() const noexcept { return cantidad_; }

        // Operacion de insercion de flujo externa
        friend std::ostream& operator <<(std::ostream& os, const LineaPedido& Lp);
    
    private:
        double precio_venta_;
        unsigned cantidad_;
};

#endif