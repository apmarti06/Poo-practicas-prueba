#include "tarjeta.hpp"
#include "usuario.hpp"
#include <iostream>

// Inicializar miembro estático
std::unordered_set<Numero> Tarjeta::tarjetas_;

// ============================================
// CONSTRUCTOR
// ============================================
Tarjeta::Tarjeta(const Numero& id, Usuario& u, const Fecha& f)
    : numero_{id}, titular_{&u}, caducidad_{f}, activa_{true} {
    
    // 1. Verificar caducidad
    if (caducidad_ < Fecha()) {
        throw Tarjeta::Caducada(caducidad_);
    }
    
    // 2. Verificar duplicidad
    std::pair<std::unordered_set<Numero>::iterator, bool> res = tarjetas_.insert(id);
    if (!res.second) {
        throw Tarjeta::Num_Duplicado(numero_);
    }
    
    // 3. Establecer relación bidireccional
    u.es_titular_de(*this);
}

// ============================================
// MÉTODO es_titular_de (Tarjeta → Usuario)
// ============================================
void Tarjeta::es_titular_de(Usuario& t) noexcept {
    titular_ = &t;
}

// ============================================
// MÉTODO type()
// ============================================
Tarjeta::Tipo Tarjeta::type() const noexcept {
    std::string num = static_cast<std::string>(numero_);
    
    if (num.empty()) return Tarjeta::Tipo::Otro;
    
    switch(num[0]) {
        case '3':
            if (num.length() > 1 && (num[1] == '4' || num[1] == '7')) {
                return Tarjeta::Tipo::AmericanExpress;
            } else {
                return Tarjeta::Tipo::JCB;
            }
        case '4':
            return Tarjeta::Tipo::VISA;
        case '5':
            return Tarjeta::Tipo::Mastercard;
        case '6':
            return Tarjeta::Tipo::Maestro;
        default:
            return Tarjeta::Tipo::Otro;
    }
}

// ============================================
// DESTRUCTOR
// ============================================
Tarjeta::~Tarjeta() {
    // 1. Si tiene titular, desvincular la tarjeta del usuario
    if (titular_ != nullptr) {
        titular_->no_es_titular(*this);
    }
    
    // 2. Eliminar de la lista de tarjetas activas
    tarjetas_.erase(numero_);
}

// ============================================
// MÉTODO PRIVADO anular_titular()
// ============================================
void Tarjeta::anular_titular() noexcept {
    titular_ = nullptr;
    activa_ = false;
}

// ============================================
// OPERADOR <
// ============================================
bool operator<(const Tarjeta& a, const Tarjeta& b) {
    return a.numero() < b.numero();
}

// ============================================
// OPERADOR << (pendiente de implementar)
// ============================================
std::ostream& operator<<(std::ostream& os, const Tarjeta& t) {
    // Implementar según necesidades
    return os;
}

std::ostream& operator<<(std::ostream& os, Tarjeta::Tipo tipo) {
    // Implementar según necesidades
    return os;
}