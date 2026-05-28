#include "numero.hpp"

// Declaraciones adelantadas
bool luhn(const Cadena& numero);

// creamos el numero de tarjeta
Numero::Numero(Cadena n) : num_t{longitud(n)} {
    char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

    // Comprobamos sus digitos y otros casos
    if (strcspn(num_t.operator const char *(), caracteres) < num_t.length()){
        throw Incorrecto(Razon::DIGITOS);
    } else {
        if (!luhn(num_t)){
            throw Incorrecto(Razon::NO_VALIDO);
        }
    }
}

// Métodos privados de clase
Cadena Numero::eliminar_espacios(const Cadena& A){
    Cadena aux(A);
    // Hacemos la conversion implicita
    const char* original = A.operator const char *();
    size_t j = 0; // hacemos copiar nuestra cad auxiliar, los que no haya _

    for (size_t i = 0; i != strlen(original); i++){
            if (!isspace(original[i])){
                // Hacemos uso del postincremento en el index
                aux[j++] = original[i];
            }
    }
    aux[j] = '\0';
    return aux;
}   

Cadena Numero::longitud(const Cadena& cad){
    Cadena res = eliminar_espacios(cad);
    // Probamos si se cumple los requisitos
    if (res.length() < 19 && res.length() > 13){
        return res;
    } else {
        throw Incorrecto(Razon::LONGITUD);
    }
}

bool operator <(const Numero& A, const Numero& B){
    return (strcmp(A, B) < 0);
}