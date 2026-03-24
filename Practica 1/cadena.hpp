#ifndef CADENAS_H
#define CADENAS_H

#include <cstring>
#include <stdexcept>
#include <cstddef>

class Cadena {
public:
    Cadena();                         // por defecto: ""
    Cadena(const char* cad);          // desde C-string (nullptr -> "")
    Cadena(size_t n, char c);         // n repeticiones de c
    Cadena(const Cadena& otra);       // constructor de copia
    Cadena& operator=(const Cadena& otra);
    Cadena& operator=(const char* a); // operadores de asignacion con un puntero char
    explicit inline operator const char*() const{return cad_;}; // operador de conversion

    // Ultimos operadores de concatenacion
    Cadena& operator+=(const Cadena& A);

    // operadores especiales mas at() observadoras
    const char& operator[](size_t i) const; // metodo const del operador (solo lectura)
    char& operator[](size_t i); // metodo no-const del operador (escritura-lectura)
    const char& at(size_t i) const;
    char& at(size_t i);

    // Funciones observadoras
    inline bool vacia() const { return len_ == 0;}
    inline size_t length() const { return len_;}

    // Funcion de string 
    Cadena substr(size_t pos, size_t n) const;

    //Operadores lógicos, acceso directo necesitado lo creamos como friend
    inline friend bool operator ==(const Cadena& A, const Cadena& B) { return strcmp(A.cad_, B.cad_) == 0; }
    inline friend bool operator !=(const Cadena& A, const Cadena& B) { return !(A == B); };
    inline friend bool operator <(const Cadena& A, const Cadena& B)  { return strcmp(A.cad_, B.cad_) < 0; }
    inline friend bool operator >(const Cadena& A, const Cadena& B)  { return !(A < B) && (A != B); }
    inline friend bool operator <=(const Cadena& A, const Cadena& B) { return !(A > B); }
    inline friend bool operator >=(const Cadena& A, const Cadena& B) { return !(A < B); }

    // Destructor
    ~Cadena();
private:
    size_t len_;
    char* cad_;
    // Funciones privadas por mi
    size_t pos_primer_caracter(const char* n) const;
};

// lo declaramos fuera de la clase pues no queremos acceder a miembros privados
Cadena operator+(const Cadena& A, const Cadena& B);

// Método privado para ver el primer caracter
inline size_t Cadena::pos_primer_caracter(const char* c) const{
    size_t i = 0;
    while (c[i] != '\0'){
        if (c[i] != ' '){
            return i;
        }
        i++;
    }
    return i; // toda la cadena son espacios
}

// operadores de indice de la clase Cadena, públicos
inline const char& Cadena::operator[](size_t i) const{
    return cad_[i];   
}

inline char& Cadena::operator[](size_t i){
    return cad_[i];
}

inline const char& Cadena::at(size_t i) const{
    if (i >= len_){
        throw std::out_of_range("Indice fuera de rango");
    }
    return cad_[i];
}

inline char& Cadena::at(size_t i){
    if (i >= len_){
        throw std::out_of_range("Indice fuera de rango");
    }
    return cad_[i];
}

#endif