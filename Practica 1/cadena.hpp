#ifndef CADENAS_H
#define CADENAS_H

#include <cstring>
#include <stdexcept>
#include <cstddef>
#include <cctype>
#include <iterator>

class Cadena {
public:
    // iteradores
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    Cadena();                         // por defecto: ""
    Cadena(const char* cad);          // desde C-string (nullptr -> "")
    Cadena(size_t n, char c);         // n repeticiones de c
    Cadena(const Cadena& otra);       // constructor de copia
    Cadena& operator=(const Cadena& otra);
    Cadena& operator=(const char* a); // operadores de asignacion con un puntero char
    explicit inline operator const char*() const {return cad_;}; // operador de conversion, el cual declaramos que sea explicito la conversión
    
    // Semántica de movimientos
    Cadena(Cadena&& otra); // constructor de movimiento
    Cadena& operator=(Cadena&& otra); // asignacion de movimiento

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

    // Operadores de flujo, se declaran friend pues no son miembros
    friend std::ostream& operator<<(std::ostream& os, const Cadena& c);
    friend std::istream& operator>>(std::istream& is, Cadena& c);

    //Operadores lógicos, acceso directo necesitado lo creamos como friend
    inline friend bool operator ==(const Cadena& A, const Cadena& B) { return strcmp(A.cad_, B.cad_) == 0; }
    inline friend bool operator !=(const Cadena& A, const Cadena& B) { return !(A == B); };
    inline friend bool operator <(const Cadena& A, const Cadena& B)  { return strcmp(A.cad_, B.cad_) < 0; }
    inline friend bool operator >(const Cadena& A, const Cadena& B)  { return !(A < B) && (A != B); }
    inline friend bool operator <=(const Cadena& A, const Cadena& B) { return !(A > B); }
    inline friend bool operator >=(const Cadena& A, const Cadena& B) { return !(A < B); }

    // Metodos no-const de funciones iteradoras
    inline iterator begin() noexcept {return cad_};
    inline iterator end() noexcept {return cad_ + len_};

    inline reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    };

    inline reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    };

    // Metodos const de funciones iteradoras
    
    inline const_iterator begin() {return cad_};
    inline const_iterator end() {return cad_ + len_};

    inline const_reverse_iterator rbegin() const noexcept { 
        return const_reverse_iterator(end()); 
    }
    
    inline const_reverse_iterator rend() const noexcept { 
        return const_reverse_iterator(begin()); 
    }

    // Implementacion requerida real 
    // ========== FUNCIONES "C" (EXPLÍCITAMENTE CONST) ==========
    inline const_iterator cbegin() const noexcept { return begin(); }
    inline const_iterator cend() const noexcept { return end(); }
    inline const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    inline const_reverse_iterator crend() const noexcept { return rend(); }


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