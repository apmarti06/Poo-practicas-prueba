#include "cadena.hpp"
#include "luhn.cpp"

#ifndef NUMERO_H
#define NUMERO_H

class Numero {
    public:
        // Tenemos 3 tipos de excepciones
        typedef enum {LONGITUD, DIGITOS, NO_VALIDO} Razon;
        /*static const char* x, y z; si se quisiera imprimir por pantalla los valores, no recoger los valores en tipo enumerados*/
        
        Numero(Cadena n);

        // Operador de conversion para imprimir tarjeta
        inline operator const char*() const {
            return num_t.operator const char *(); // es clase Cadena pues entonces tiene esta func()
        }

        inline Cadena numero() const noexcept { return num_t;}

        // Sobrecargamos operadores de clase Numero
        friend bool operator<(const Numero& A, const Numero& B);

        // clase de excepción
        class Incorrecto {
            public:
                // creamos la clase y su lanzador de excepciones
                Incorrecto(const Razon& r) : razon_(r) {}
                const Razon& razon() { return razon_; }
            private:
                Razon razon_;
        };

    private:
        Cadena num_t;
        Cadena eliminar_espacios(const Cadena&); // devolvemos la cadena sin espacios
        Cadena longitud (const Cadena&); // comprobamos la longitud
};

#endif