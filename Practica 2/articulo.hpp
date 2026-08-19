#ifndef TARJETA_HPP
#define TARJETA_HPP
#include "fecha.hpp"
#include "cadena.hpp"
#include <iostream>
#include <iomanip> // Necesario para std::fixed y std::setprecision

// IMPORTANTÍSIMO QUE MIEMBROS CLASE FECHA SEAN PÚBLICOS PARA f_publi().año(), sea correcto
class Articulo {
    public:
        Articulo(int c, const Cadena& t, Fecha f, float p, int n = 0);

        // Metodos de observadores de clase
        inline int referencia() const {return cod_referencia;}
        inline Cadena titulo() const {return titulo_;}
        inline Fecha f_publi() const {return fecha_;}

        // Creamos métodos const no-const
        inline float precio() const {return precio_;}
        inline float& precio() {return precio_;}
        inline int stock() const {return numEjemplares_;}
        inline int& stock() {return numEjemplares_;}

    private:
    // Atributos no modificables
        const int cod_referencia;
        const Cadena titulo_;
        const Fecha fecha_;
    // Atributos modificables;
        float precio_;
        int numEjemplares_;
};

#endif