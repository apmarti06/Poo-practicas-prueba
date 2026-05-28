#include "lineaPedido.hpp"

std::ostream& operator <<(std::ostream& os, const LineaPedido& Lp){
    os << std::fixed << std::setprecision(2) << Lp.precio_venta() << "$\t" << Lp.cantidad();
    return os;
}