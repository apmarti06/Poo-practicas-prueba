#include "./cadena.hpp"

// Constructor por defecto
Cadena::Cadena() : len_{0}, cad_{new char[1]} {
    cad_[0] = '\0';
}

// copiamos la cadena de un string a teclado
Cadena::Cadena(const char* cad) {
    if (cad == nullptr) {
        // misma implementacion que el por defecto (podríamos llamarlo y devolver dicha cadena)
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
    // no se le asigna, pues seria que un puntero apuntase al mismo espacio, donde al salir de la funcion se daría un delete,
    // lo cual no queremos ya que estaría mal
    std::strcpy(cad_, otra.cad_);
}

// Sobrecargamos el operador de asignación dos veces
Cadena& Cadena::operator=(const Cadena& otra) {
    if (this != &otra) { // importante, si fueran iguales el delete[] borraría la cadena de memoria y luego no podríamos copiarla
        char* nuevo = new char[otra.len_ + 1];
        std::strcpy(nuevo, otra.cad_);
        delete[] cad_; // borramos la basura donde apuntase cad_ para evitar fugas de memoria
        cad_ = nuevo;
        len_ = otra.len_;
    }
    return *this;
}

Cadena& Cadena::operator=(const char* copia){ // a = "hola";
    // usamos el constructor con cadena de bajo nivel, para pasarlo luego como objeto
    Cadena otra(copia);
    *this = otra;
    return *this;
}

Cadena& Cadena::operator+=(const Cadena& A){ // b += a 
    char* temp = new char[std::strlen(A.cad_) + std::strlen(cad_) + 1];
    std::strcpy(temp, cad_);
    std::strcat(temp, A.cad_);
    delete[] cad_;
    cad_ = temp; 
    return *this;
}   

Cadena operator +(const Cadena& A, const Cadena& B){ // c = a + b
    Cadena temp = A;
    temp += B;
    return temp;
}

Cadena Cadena::substr(size_t pos, size_t n) const{ // obtenemos una parte de una cadena 
    if (pos + n > len_){   // Precondiciones manejando errores
        throw std::out_of_range("Índice fuera de rango");
    }
    
    size_t m = len_ - pos; 
    
    char* nueva = new char[m + 1]; //ampliamos, añadiendo el caracter nulo
    for (size_t i = 0, j = pos; i < m; i++, j++){ // añadimos la cadena substraída
        nueva[i] = cad_[j];
    }

    nueva[m] = '\0'; // caracter nulo al final
    
    Cadena resultado(nueva); // creamos un objeto de tipo Cadena con la subcadena
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
    
    //  Si se llega al final antes de encontrar palabra -> cadena vacía
    if (!is) {
        c = "";
        return is;
    }

    // 2) Leer la palabra sin consumir el espacio final, asegurandonos que sea un char
    while (is && !std::isspace(is.peek()) && i < 32) {
        buffer[i++] = static_cast<char>(is.get());
    }

    buffer[i] = '\0';
    c = buffer;

    return is;
}

// Como hacemos una conversion explicita, (requerida por el enunciado) no podemos hacer una conversion implicita, por lo que debemos hacer un cast a const char* para poder imprimirlo
std::ostream& operator<<(std::ostream& os, const Cadena& c){
    os << c.operator const char *();
    return os;
}

// La semantica de movimiento se encarga de borrar automaticamente la memoria de un objeto que ya no se va a usar, evitando fugas de memoria y mejorando el rendimiento al evitar copias innecesarias. Esto es especialmente útil en contenedores y algoritmos que manejan grandes cantidades de datos, donde la eficiencia es crucial.

Cadena::Cadena(Cadena&& otra) noexcept : len_{otra.len_}, cad_{otra.cad_} {
    otra.len_ = 0;
    otra.cad_ = nullptr; 
}

Cadena& Cadena::operator=(Cadena&& otra) noexcept {
    if (this != &otra){ // si son iguales omitimos el cambio
        delete[] cad_;
        len_ = otra.len_;
        cad_ = otra.cad_;
        // Una vez reasignado el puntero cambiamos las cadenas
    }
    otra.cad_ = 0;
    otra.cad_ = nullptr;
    
    return *this;
}