#include "cadena.hpp"
#include <stdexcept>
#include <cctype>

#ifndef CLAVE_H
#define CLAVE_H

class Clave {
    public:
        // Constantes estáticas para los errores
        static const char* CORTA;
        static const char* ERROR_CRYPT;

        // Definimos la clave que respete sus propiedades, con una cadena de bajo nivel
        // Ya que nuestra clase Cadena hará la conversion implícita
        Clave(const char* cad);

        // Miembros de la clase
        Cadena clave() const { return passwd_cif; }
        bool verifica (const char* cad) const;

        // Para evaluar errores
        class Incorrecta: public std::exception {
            public:
                 // Constructor de la excepción, recibe el mensaje de error
                Incorrecta(const char* e) : error_(e) {}
                const char* razon() const noexcept {return error_; }
            private:
                const char* error_;
        };

    private:
        Cadena passwd_cif;
        // Conjunto de caracteres entre los que escoger la «sal» para encriptar las claves.
        // static const char caracteres_validos [];

};


#endif