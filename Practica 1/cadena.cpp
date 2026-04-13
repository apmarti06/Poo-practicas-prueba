#include "./cadena.hpp"

// Constructor por defecto
Cadena::Cadena() : len_{0}, cad_{new char[1]} {
    cad_[0] = '\0';
}

// copiamos la cadena de un string a teclado
Cadena::Cadena(const char* cad) {
    if (cad == nullptr) {
        len_ = 0;
        cad_ = new char[1];
        cad_[0] = '\0';
    } else {
        len_ = std::strlen(cad);
        cad_ = new char[len_ + 1];
        std::strcpy(cad_, cad);
    }
}

Cadena::Cadena(size_t n, char c) : cad_{new char[n + 1]}, len_{n} {
    for (size_t i = 0; i < n; ++i) cad_[i] = c; // se llenara del caracter introducido
    cad_[n] = '\0';
}

// CONSTRUCTOR DE COPIA DEFINIDO
Cadena::Cadena(const Cadena& otra) : cad_{new char[otra.len_ + 1]}, len_{otra.len_} {
    std::strcpy(cad_, otra.cad_);
}

// Sobrecargamos el operador de asignación dos veces
Cadena& Cadena::operator=(const Cadena& otra) {
    if (this != &otra) {
        char* nuevo = new char[otra.len_ + 1];
        std::strcpy(nuevo, otra.cad_);
        delete[] cad_;
        cad_ = nuevo;
        len_ = otra.len_;
    }
    return *this;
}

Cadena& Cadena::operator=(const char* copia){
    // usamos el constructor de copia para pasarlo luego como objeto
    Cadena otra(copia);
    *this = otra;
    return *this;
}

Cadena& Cadena::operator+=(const Cadena& A){
    char* temp = new char[std::strlen(A.cad_) + std::strlen(cad_) + 1];
    std::strcpy(temp, cad_);
    std::strcat(temp, A.cad_);
    delete[] cad_;
    cad_ = temp; 
    return *this;
}   

Cadena operator +(const Cadena& A, const Cadena& B){
    Cadena temp = A;
    temp += B;
    return temp;
}

Cadena Cadena::substr(size_t pos, size_t n) const{
    // Precondiciones manejando errores
    if (pos > len_){
        throw std::out_of_range("Índice fuera de rango");
    }

    if (pos + n > len_){
        n = len_ - pos; // la variamos para que no copie datos que no existan
    }
    
    char* nueva = new char[n + 1]; //ampliamos, añadiendo el caracter nulo
    for (size_t i = 0, j = pos; i < n; i++, j++){ // añadimos la cadena substraída
        nueva[i] = cad_[j];
    }

    nueva[n] = '\0';
    // creamos nuestra nueva clase y retornamos
    Cadena resultado(nueva);
    // aseguramos que nueva se borre de la memoria
    delete[] nueva;
    nueva = nullptr;

    return resultado;
}

Cadena::~Cadena() {
    if (!vacia()){
        delete[] cad_;
        cad_ = nullptr;
    }
}

// Operacion de inserción 
std::istream& operator>>(std::istream& is, Cadena& c){
    char buffer[33]; // reservamos espacio para el límite (32 caracteres + "\0")
    size_t i = 0;

    // 1. Buscamos si hay espacio inicial
    while (is && std::isspace(is.peek())){
        is.get();
    }
    // Si se llega al final antes de encontrar palabra -> cadena vacía
    if (!is) {
        c = "";
        return is;
    }

    // 2) Leer la palabra sin consumir el espacio final
    while (is && !std::isspace(is.peek()) && i < 32) {
        buffer[i++] = static_cast<char>(is.get());
    }

    buffer[i] = '\0';
    c = buffer;

    return is;
}

std::ostream& operator<<(std::ostream& os, const Cadena& c){
    os << 
}


Cadena::Cadena(Cadena&& otra) noexcept : len_{otra.len_}, cad_{otra.cad_} {
    otra.len_ = 0;
    otra.cad_ = new char[1];
    otra.cad_[0] = '\0'; 
}

Cadena& Cadena::operator=(Cadena&& otra) noexcept{
    if (this != &otra){ // si son iguales omitimos el cambio
        delete[] cad_;
        len_ = otra.cad_;
        cad_ = otra.cad_;
        // Una vez reasignado el puntero cambiamos las cadenas
        otra.cad_ = 0;
        otra.cad_ = new char[1];
        otra.cad_[0] = '\0';
    }
    
    return *this;
}