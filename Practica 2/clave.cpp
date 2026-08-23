#include "clave.hpp"
#include <unistd.h> //Para usar char* crypt(const char* contraseña, const char* sal)
#include <cstdlib> // srand()
#include <random>  // random()

// Definimos las constantes estáticas, SIEMPRE EN EL CPP o en un inline, si usamos polimorfismo
const char* Clave::CORTA = "Contraseña demasiado corta.";
const char* Clave::ERROR_CRYPT = "Error al cifrar la contraseña.";

// Esta es privada, no se puede usar como miembro de clase
const char Clave::caracteres_validos[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

// Prototipo de la función
char* crypt(const char* contraseña, const char* sal);
/*El primer parámetro es la contraseña a encriptar. La sal, segundo parámetro, debe ser una
cadena de dos caracteres por lo menos, sin contar el terminador.

No importa si esta cadena es más larga, pues crypt() solo necesita los dos 
primeros caracteres e ignora el resto. Estos tienen que ser dos cualesquiera elegidos entre
los 64 del conjunto {a−zA−Z0−9./} (26 letras minúsculas, 26 mayúsculas, 10 dígitos
y 2 caracteres más, '.' y '/'). 

La función crypt() los emplea para variar el algoritmo en uno de 4 096 modos diferentes*/

Clave::Clave(const char* cad) : passwd_cif{cad} { // la inicializamos en la lista inicializadora para guardarla
    // Primer límite que la cadena sea demasiada corta (para crypt())
    if (passwd_cif.length() < 5){
        throw Clave::Incorrecta(Clave::CORTA);  
    } 
    else {
        try {
            // Preparamos con cifrado, para que nuestro crypt sea correcto, donde usamos static para que la semilla no varíe
            static std::random_device random;
            static std::mt19937 gna{random()};
            static std::size_t n {sizeof(caracteres_validos) - 1}; // n = 64

            std::uniform_int_distribution<std::size_t> uniforme(0, n - 1);
            // Escogemos 2 aleatorios de caracteres validos y el terminador
            const char cifrado[3] = {caracteres_validos[uniforme(gna)], caracteres_validos[uniforme(gna)], '\0'}; 
            
            // Una vez pasado bien los parametros llamamos y, si se encripta mal llamamos a la clase Incorrecta
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
    // Comparamos la encriptacion de la clave que hemos metido, pasandolos a *char para usar strcmp
    return !(strcmp(crypt(cad, passwd_cif.operator const char *()), passwd_cif.operator const char *()));
}