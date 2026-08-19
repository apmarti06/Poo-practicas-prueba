#include "cadena.hpp"
#include "luhn.cpp"

#ifndef NUMERO_H
#define NUMERO_H

class Numero {
    public:
        // Tenemos 3 tipos de excepciones 
        // 1. Longitud menor que 13 o mayor que 19
        // 2. Algún caracter (solo números)
        // 3. Algoritmo de luhn ha producido un fallo
        typedef enum {LONGITUD, DIGITOS, NO_VALIDO} Razon;

        // Operador de conversion para imprimir tarjeta, llamando de forma explicita al de Cadena
        inline operator const char*() const {
            return num_t.operator const char *(); // es clase Cadena pues entonces tiene esta func()
        }

        // Método observadora
        inline Cadena numero() const noexcept { return num_t;}

        // Sobrecargamos operadores de clase Numero, podemos implementarlo friend o usando el miembro numero()
        friend bool operator<(const Numero& A, const Numero& B);

        // clase de excepción, en este caso por enunciado solo incluimos
        // las del tipo Razón, sin capturar excepciones ajenas
        class Incorrecto {
            public:
                Incorrecto(const Razon& r) : razon_{r} {}
                const Razon& razon() {return razon_;}
            private:
                Razon razon_;
        };

        // Constructor de la clase Número
        Numero(Cadena n);

    private:
        Cadena num_t; // Atributo de clase

        // Metodos privados de Cada Número, donde se quiten el espacio + validar número
        Cadena eliminar_espacios(const Cadena&); // devolvemos la cadena sin espacios
        Cadena validar_longitud(const Cadena&); // comprobamos que el número existe
};

#endif