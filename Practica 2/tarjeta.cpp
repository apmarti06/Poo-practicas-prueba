#include "tarjeta.hpp"

// lo declaramos ya que es un miembro estatico de la clase
std::set<Numero> Tarjeta::tarjetas_;

std::unordered_set<Numero>::iterator It; // recordamos que unordered_set (1. clave, 2 valor que siempre usa un booleano)

Tarjeta::Tarjeta(const Numero& n, Usuario& u, const Fecha& f) : numero_{n}, titular_{u}, caducidad_{f}, activa{true} {
    // vemos si la caducidad de la tarjeta ya ha pasado
    if(caducidad_ < Fecha()){ // comparamos la del sistema
        throw TARJETA::Caducada(caducidad_);
    }

    // Comprobamos la duplicidad, viendo al usar el iterador a los eltos de la tarjeta
    // si la insercion es posible el valor de los pares sera true (por defecto) en el bool si no se puede
    // ya que esta repetido, seguira false por lo que comparamos apartir de este valor

    std::pair<It, bool> res = tarjetas_.insert(id);
    if (!res.second){
        throw Tarjeta::Num_Duplicado(numero_);
    }

    // Si no esta asignada lo asignamos a este usuario la tarjeta, haciendo uso de la asociacion de la clase usuario
    titular_->es_titular_de(*this);
} 

Tipo Tarjeta::tipo() const noexcept { // evaluamos los 6 casos que tenemos, y usamos el [] de cadena
    switch(numero_[0]){
        case '3':
            if(numero_[1] == 4 || numero_[1] == 7){
                return Tarjeta::Tipo::AmericanExpress;
            } else {
                return Tarjeta::Tipo::JCB;
            }
            break;
        case '4':
            return Tarjeta::Tipo::VISA;
            break;
        case '5':
            return Tarjeta::Tipo::VISA;
            break;
        case '6':
            return Tarjeta::Tipo::Mastercard;
            break;
        default:
            return Tarjeta::Tipo::Otro;
            break;
    }
}

Tarjeta::~Tarjeta(){
    // Primero desvinculamos de su titular, todas las tarjetas
    if (Usuario* user = const_cast<Usuario*>(titular_)) 
        user->no_es_titular_de(*this);
    // eliminamos despues de desvincular
    tarjetas_.erase(numero_);
}

bool operator<(const Tarjeta& A, const Tarjeta& B){
    return (A.numero() < B.numero());
}


// Metodos privados, donde al eliminar el Usuario, rompemos el enlace de la tarjeta - Usuario
void Tarjeta::anular_titular() noexcept{
    if(titular_ != nullptr){
        titular_ = nullptr;
        activa = false;
    }
}

