#ifndef TARJETA_HPP
#define TARJETA_HPP
#include "fecha.hpp"
#include "cadena.hpp"
#include <iostream>
#include <iomanip> // Necesario para std::fixed y std::setprecision

class Articulo {
    public:
        Articulo(int c, const Cadena& t, Fecha f, float p, int n);

        // Metodos de observadores de clase
        inline int referencia() const {return cod_referencia;}
        inline Cadena titulo() const {return titulo_;}
        inline Fecha f_publi() const {return fecha_;}
        inline float precio() const {return precio_;}
        // Esta puede sufrir modificaciones
        inline int stock() {return numEjemplares_;}

    private:
    // Atributos no modificables
        int cod_referencia;
        Cadena titulo_;
        Fecha fecha_;
    // Atributos modificables;
        float precio_;
        int numEjemplares_;
};



#endif