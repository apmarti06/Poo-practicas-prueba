#include "clave.hpp"
#include <unistd.h> //crypt()
#include <cstdlib> // srand()
#include <random>  //


// Definimos las constantes estáticas
const char* Clave::CORTA = "Contraseña demasiado corta.";
const char* Clave::ERROR_CRYPT = "Error al cifrar la contraseña.";

char* crypt(const char* contraseña, const char* sal);
// crypt usa -> char* crypt(const char* contraseña, const char* sal)

Clave::Clave(const char* cad) : passwd_cif(cad) {
    if (passwd_cif.length() < 5){
        throw Clave::Incorrecta(Clave::CORTA);
    } else {
            
        try {
            // Preparamos con cifrado, para que nuestro crypt sea correcto
            const char* valores = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
            std::random_device random;
            std::mt19937 gna{random()};
            std::size_t n {sizeof(valores) - 1}; // n = 64
            std::uniform_int_distribution<std::size_t> uniforme(0, n - 1);
            // Escogemos 2 aleatorios de caracteres validos y el terminador
            const char cifrado[3] = {valores[uniforme(gna)], valores[uniforme(gna)], '\0'}; 

            if (crypt(cad, cifrado)){
                passwd_cif = crypt(cad, cifrado);
            } else {
                throw Clave::Incorrecta(Clave::ERROR_CRYPT);
            }
            
        } catch(...){ // para errores fuera de nuestro alcance
            throw Clave::Incorrecta("Error desconocido");
        }
    }
} 

bool Clave::verifica(const char* cad) const {
    // Comparamos la encriptacion de la clave que hemos metido
    // Concuerda con una de las claves
    return !(strcmp(crypt(cad, passwd_cif.operator const char *()), passwd_cif.operator const char *()));
}

