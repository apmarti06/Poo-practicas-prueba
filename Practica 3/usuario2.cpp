#include "usuario.hpp"
#include "tarjeta.hpp"
#include <iostream>
#include <iomanip>

// Inicializar miembro estático
std::unordered_set<Cadena> Usuario::id_usuarios;

// ============================================
// CONSTRUCTOR
// ============================================
Usuario::Usuario(Cadena id, Cadena n, Cadena ap, Cadena dir, Clave c)
    : identificador_{id}, nom_{n}, apell_{ap}, direccion_{dir}, clave_{c} {
    
    // Verificar ID único
    std::pair<std::unordered_set<Cadena>::iterator, bool> res = id_usuarios.insert(id);
    if (!res.second) {
        throw Id_duplicado(id);
    }
}

// ============================================
// DESTRUCTOR
// ============================================
Usuario::~Usuario() {
    // 1. Anular el titular de todas las tarjetas
    for (Usuario::Tarjetas::iterator it = tarjetas_.begin(); 
         it != tarjetas_.end(); 
         ++it) {
        it->second->anular_titular();
    }
    
    // 2. Eliminar el ID del conjunto global
    id_usuarios.erase(identificador_);
}

// ============================================
// ASOCIACIÓN: Usuario → Tarjeta
// ============================================
void Usuario::es_titular_de(Tarjeta& t) {
    // 1. Verificar que la tarjeta pertenece a este usuario
    if (t.titular() != this) {
        return;
    }
    
    // 2. Añadir la tarjeta al mapa del usuario
    tarjetas_.insert(std::make_pair(t.numero(), &t));
    
    // 3. Establecer la relación bidireccional (Tarjeta → Usuario)
    t.es_titular_de(*this);
}

void Usuario::no_es_titular(Tarjeta& t) {
    // 1. Romper el enlace desde la tarjeta
    t.anular_titular();
    
    // 2. Eliminar la tarjeta del mapa del usuario
    tarjetas_.erase(t.numero());
}

// ============================================
// ASOCIACIÓN: Usuario → Artículo
// ============================================
void Usuario::comprar(Articulo& a, size_t cant) {
    if (cant == 0) {
        articulos_.erase(&a);
        return;
    }
    
    Usuario::Articulos::iterator it = articulos_.find(&a);
    
    if (it == articulos_.end()) { // si no hay articulos, lo insertaos
        articulos_.insert(std::make_pair(&a, cant));
    } else {
        it->second += cant;
        if (it->second <= 0) {
            comprar(a, 0); // eliminar si la cantidad es cero, donde si es negativo igual
        }
    }
}

// ============================================
// OPERADOR <<
// ============================================
std::ostream& operator<<(std::ostream& os, const Usuario& u) {
    os << u.id() << " [" << static_cast<const char*>(u.clave()) << "] "
       << u.nombre() << " " << u.apellidos() << std::endl;
    os << u.direccion() << std::endl;
    os << "Tarjetas:" << std::endl;
    
    for (Usuario::Tarjetas::const_iterator it = u.tarjetas().begin();
         it != u.tarjetas().end();
         ++it) {
        os << "  " << it->first << " (";
        
        switch (it->second->type()) {
            case Tarjeta::VISA: os << "VISA"; break;
            case Tarjeta::Mastercard: os << "Mastercard"; break;
            case Tarjeta::Maestro: os << "Maestro"; break;
            case Tarjeta::JCB: os << "JCB"; break;
            case Tarjeta::AmericanExpress: os << "AmericanExpress"; break;
            default: os << "Otro"; break;
        }
        os << ") Caduca: " << it->second->caducidad();
        if (!it->second->activa()) os << " (INACTIVA)";
        os << std::endl;
    }
    
    return os;
}

// ============================================
// MOSTRAR CARRITO
// ============================================
void mostrar_carro(std::ostream& os, const Usuario& u) {
    const Usuario::Articulos& carro = u.compra();
    
    if (carro.empty()) {
        os << "Carrito vacío" << std::endl;
        return;
    }
    
    os << "Carrito de compra de " << u.id() 
       << " [Artículos: " << u.n_articulos() << "]" << std::endl;
    os << " Cant. Artículo" << std::endl;
    os << std::setw(95) << std::setfill('=') << "" << std::endl;
    
    for (Usuario::Articulos::const_iterator it = carro.begin();
         it != carro.end();
         ++it) {
        os << std::setw(4) << std::setfill(' ') << it->second
           << "  [" << it->first->referencia() << "] "
           << "\"" << it->first->titulo() << "\", "
           << it->first->f_publi().año() << ". "
           << std::fixed << std::setprecision(2)
           << it->first->precio() << " €"
           << std::endl;
    }
}