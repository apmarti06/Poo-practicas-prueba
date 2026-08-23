#ifndef NUMERO2_H
#define NUMERO2_H


#include <functional>
#include "C:\Users\Usuario\c++\poo\Practica 0 y 1\cadena.hpp"
#include "C:\Users\Usuario\c++\poo\Practica 2\luhn.cpp"

// Implementamos la clase Numero utilizando los algoritmos de la STL remove_if y find_if.

class Numero {
    public:
        // Tenemos 3 tipos de excepciones
        typedef enum {LONGITUD, DIGITOS, NO_VALIDO} Razon;
        /*static const char* x, y z; si se quisiera imprimir por pantalla los valores, no recoger los valores en tipo enumerados*/
        Numero(const Cadena& n);

        // Operador de conversion para imprimir tarjeta
        inline operator const char*() const {
            return num_t.operator const char *(); // es clase Cadena pues entonces tiene esta func()
        }

        inline Cadena numero() const noexcept { return num_t;}
x
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

        // Clase anidada para detectar espacios y que sea un número

        // Hacemos uso de std::unary_function para representar la funcion en dos partes
        // el argumento de entrada (char) y el tipo de salida (bool), donde el resultado comprueba 
        // si lo que se ha pasado es correcto o no

        class EsBlanco : public std::unary_function<char, bool>{
            public:
                bool operator() (char caracter) const {
                    return std::isspace(static_cast<unsigned char>(caracter)); 
                }
        };
        
        class EsDigito : public std::unary_function<char, bool> {
            public:
                bool operator() (char caracter) const {
                    return std::isdigit(static_cast<unsigned char>(caracter));
                }
        };

    private:
        Cadena num_t;
        // metodos privados sustituidos por los algoritmos STL
};

#endif