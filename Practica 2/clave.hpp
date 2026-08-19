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

        // Miembros de la clase (Uno que te ofrece la contraseña cifrada y la otra te verifica si es correcta)
        Cadena clave() const { return passwd_cif; }
        bool verifica (const char* cad) const;

        // Para evaluar errores si se cifra mal la contraseña o es demasiado corta
        class Incorrecta: public std::exception { // hacemos esto para atrapar errores que se escapen de nuestro alcance
            public:
                 // Constructor de la excepción, recibe el mensaje de error
                Incorrecta(const char* e) : error_{e} {}
                const char* razon() const noexcept {return error_; }
            private:
                const char* error_;
        };

    private:
        // Atributo de la clase Clave
        Cadena passwd_cif;

        // Miembros estaticos de la clase clave privados
        static const char caracteres_validos[];
};

#endif