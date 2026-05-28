#include "usuario.hpp"

// Inicializacion del conjunto global
std::unordered_set<Cadena> Usuario::id_usuarios_;

typedef std::unordered_set<Cadena>::iterator It_ids;
typedef Usuario::articulos_::iterator IT_art;

Usuario::Usuario(Cadena id, Cadena n, Cadena ap, Cadena dir, Clave c) : identificador_{id}, nom_{n},
 apell_{ap}, direccion_{dir}, clave_{c} {
    // clase pair formado por un iterador que apunta al contenedor que contiene todas las claves del usuario,
    //  y un booleano que indica si la insercion es erronea o válida
    // consultamos en nuestro diccionario de claves si existe, por ID, second es un booleano
    std::pair<It, bool> res = id_usuarios_.insert(id);

    // sino ha sido correcta
    if (!res.second){
        throw Usuario::Id_duplicado(id);
    }
}

Usuario::~Usuario(){
    // eliminamos todas sus tarjetas, antes de borrarlo, usando auto para evitar llamar al iterador
    for (auto i = tarjetas_.begin(); i != tarjetas_.end(); i++){ //Usuario::tarjetas_::const_iterator i 
        (i->second)->anular_titular();
    }

    // eliminamos el usuario de la lista correspondiente
    id_usuarios_.erase(identificador_);
}

// Enlaces de clases

void Usuario::es_titular_de(Tarjeta& T){
    // hacemos la asociacion Usuario 1 --- N tarjetas
    if (this == T.titular()){
        tarjetas_.insert(std::make_pair(T.numero(), &T)); // creamos la asociacion, donde le metemos la clave numero, y la tarjeta T
    }
}

void Usuario::no_es_titular(Tarjeta& T){
    // rompemos el enlace
    T.anular_titular();
    tarjetas_.erase(T.numero());
}

// Aqui podemos tanto introducir como borrar articulos
void Usuario::comprar(Articulo& A, size_t cant){
    if (cant > 0){
        articulos_.insert(std::make_pair(&A, cant));
    } else {
        // eliminamos los articulos que sean tal como A, viendo condiciones
        It_art i = articulos_.find(A);

        // sino lo encontramos salimos de esta operación
        if (i != articulos_.end()){
            // borramos todo, o eliminamos producto segun condiciones
            if (i->second <= cant){
                articulos_.erase(&A);
            } else {
                articulos_.second -= cant;
            }
        }
    }
}

// Operador de flujo de salida
std::ostream& operator <<(std::ostream& os, const Usuario& user){
    os << user.id() << "[" << user.clave().operator const char*() <<  "]" << user.nombre() 
    << user.apellidos() << std::endl;

    os << user.direccion() << std::endl;
    os << "Tarjetas" << std::endl; 

    for (const Usuario& lista_tarjetas: U.tarjetas()){
        os << (lista_tarjetas->second).tipo() << std::endl; 
        os << (lista_tarjetas->first).numero() << std::endl; 
        os << user.nombre() << user.apellidos() << std::endl; // usar conversor a mayus
        os << "Caduca en:" << (lista_tarjetas->second).caducidad() << std::endl; 
    }
}

// mostramos el carrito
void mostrar_carro(std::ostream& os, const Usuario& U){
    os << "Carrito de compra de" << U.id() << "[Articulos: " << U.n_articulos() << "] \n"
    << " Cant. Articulo" << std::endl;

    os << std::setw(95)<<std::setfill('=') << '' << std::endl; // formato deseado ========

    // Hacemos llamada a la lista de articulos con las claves asociadas <Articulo*, cantidad>
    for (const Usuario& compra: U.compra()){
        os << std::setw(4)<<std::setfill('') << compra->second << "[" << (compra->first).referencia << "]" 
        << "'" << (compra->first).titulo() << "'" << (compra->first).f_publi.año() << 
        (compra->first).precio << std::endl;
    }
}

/*// Para P2 y ss.
// Especializaci ón de la plantilla std::hash<Key> para definir la función hash
// a usar con contenedores asociativos desordenados con claves de tipo Cadena,
// unordered_[set|map|multiset|multimap].
namespace std { // Estaremos dentro del espacio de nombres std.
    template <> // Es una especializaci ón de una plantilla para Cadena.
    struct hash<Cadena> { // Es una clase con solo un operador público.
        size_t operator() (const Cadena& cad) const // El operador función.
        {
        hash<string> hs; // Creamos un objeto hash de string.
        auto p{(const char*)(cad)}; // Convertimos cad a cadena de bajo nivel.
        string s{p}; // Creamos un string desde la cadena de b. nivel .
        size_t res{hs(s)}; // El hash del string . Como hs.operator()(s);
        return res; // Devolvemos el hash del string. 


        Otra forma: return hash<string>{}((const char*)(cad));
        }
    };
}
*/