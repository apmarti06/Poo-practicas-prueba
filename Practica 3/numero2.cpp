#include "numero2.hpp"
#include <algorithm>

// Declaraciones adelantadas
bool luhn(const Cadena& numero);

//Modificamos nuestra implementacion del numero
Numero::Numero(const Cadena& n) {
    // hacemos uso de los algoritmos
    Cadena aux(n);

    // Usamos primero, remove_if para quitar espacios
    Cadena::iterator quitaEspacios = std::remove_if(aux.begin(), aux.end(), EsBlanco()); 

    // Modificamos internamente el Numero, fisicamente
    if (quitaEspacios != aux.end()){
        aux = aux.substr(0, quitaEspacios-aux.begin());
    }
    
    // Usamos ahora find_if, buscando caracteres que no sean digitos
    Cadena::iterator it_num = std::find_if(aux.begin(), aux.end(), EsDigito());

    // Probamos errores, sea digitos correcto, longitud deseada y algoritmo sea correcto
    if (it_num != aux.end()){
        throw Incorrecto(Razon::DIGITOS);
    }

    if (aux.length() < 13 || aux.length() > 19){
        throw Incorrecto(Razon::LONGITUD);
    }

    // comprobamos que sea correcto el numero
    if (!luhn(aux)){
        throw Incorrecto(Razon::NO_VALIDO);
    }

    // si todo es correcto el num es valido
    num_t = aux;

}

bool operator <(const Numero& A, const Numero& B){
    return (strcmp(A, B) < 0);
}