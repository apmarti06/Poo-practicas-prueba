#include "tarjeta.hpp"

class Usuario;
// lo declaramos ya que es un miembro estatico de la clase
std::unordered_set<Numero> Tarjeta::tarjetas_;
typedef std::unordered_set<Numero>::iterator It; // recordamos que unordered_set (1. clave, 2 valor que siempre usa un booleano)

// Asociación bidireccional entre Usuario y Tarjeta
void Tarjeta::es_titular_de(const Usuario& t) noexcept {
    // Este método es llamado desde Usuario::es_titular_de
    // para establecer la relación bidireccional
    titular_ = &t;
}


Tarjeta::Tarjeta(const Numero& id, const Usuario& u, const Fecha& f) : numero_{id}, titular_{&u}, caducidad_{f}, activa_{true} {
    // vemos si la caducidad de la tarjeta ya ha pasado
    if(caducidad_ < Fecha()){ // comparamos la del sistema, pues es la actual
        throw Tarjeta::Caducada(caducidad_);
    }

    // Comprobamos la duplicidad, viendo al usar el iterador a los eltos de la tarjeta
    // si la insercion es posible el valor derecho del par sera true (por defecto) en el bool si no se puede
    // ya que esta repetido, seguira false por lo que comparamos apartir de este valor

    std::pair<It, bool> res = tarjetas_.insert(id);
    if (!res.second){
        throw Tarjeta::Num_Duplicado(numero_);
    }

    // Si no esta asignada lo asignamos a este usuario la tarjeta, haciendo uso de la asociacion de la clase usuario
    titular_->es_titular_de(*this); // this es un puntero a la tarjeta, por lo que desreferenciamos para pasarle la referencia
}

Tarjeta::Tipo Tarjeta::type() const noexcept { // evaluamos los 6 casos que tenemos, y usamos el [] de cadena, pues se evalua con el primer digito (carácter)
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
    if (titular_ != nullptr)  // al ser const conversion con const_cast, donde guardamos el puntero para borrarlo
        const Usuario* user = const_cast<Usuario*>(titular_);
        titular_->no_es_titular_de(*this);  // Esto solo anula, no elimina, pues eliminar sería un fallo

    // Eliminamos la tarjeta del conjunto global de tarjetas, solo si existe
    It i = tarjetas_.find(numero_);
    if (i != tarjetas_.end()){
        tarjetas_.erase(i);
    }    
}

bool operator<(const Tarjeta& A, const Tarjeta& B){ // sobrecarga donde A.numero(), llama a los static<cast>, haciendo la conversion explicita de cadena
    return (A.numero() < B.numero());
}

// Metodos privados, donde al eliminar el Usuario, rompemos el enlace de la tarjeta - Usuario
void Tarjeta::anular_titular() noexcept{
    // si apuntamos a algo, al asegurarnos que es const (debería almacenar por cojones algo), borramos para ese usuario la tarjeta
    if(titular_ != nullptr){
        titular_ = nullptr;
        activa_ = false;
    } 
}

