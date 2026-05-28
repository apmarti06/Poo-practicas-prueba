#include "articulo.hpp"
#include <iomanip>  // Para manipular la salida, como los decimales 

// Indicamos en el num_ejemplares que sea por defecto el num_ejemplares 0
Articulo::Articulo(int c, const Cadena& t, Fecha f, float p, int n = 0) : cod_referencia(c), titulo_(t),
fecha_(f), precio_(p), numEjemplares_(n) {}

// Definición del operador de inserción en flujo de salida
std::ostream& operator<<(std::ostream& os, const Articulo& A) {
    // Usamos manipuladores para dar formato a la salida
    os << "[" << A.referencia() << "] \"" << A.titulo() << "\", "  << A.f_publi().año() 
    << ". " << std::fixed << std::setprecision(2)  // Para dos decimales
    << A.precio() << " €";
    return os;
}


