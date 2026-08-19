#include "usuario.hpp"

// Inicializacion del conjunto global (por defecto)
std::unordered_set<Cadena> Usuario::id_usuarios;

// Tenemos constancia de todos las veces que se añade un nuevo usuario al sistema (sin conocer claves)
Usuario::Usuario(Cadena id, Cadena n, Cadena ap, Cadena dir, Clave c) : identificador_{id}, nom_{n},
 apell_{ap}, direccion_{dir}, clave_{c} {
    //pair formado por un iterador que apunta al contenedor que contiene todas las claves del usuario,
    // y un booleano que indica si la insercion es erronea o válida

    // definimos el tipo para ver si el iterador apunta a algún punto del contenedor, sino devolvera al insertar el bool = false    
    typedef std::unordered_set<Cadena>::iterator It_ids;
    std::pair<It_ids, bool> res = id_usuarios.insert(id); // probamos si el id coincide con alguno del id_usuario

    // consultamos en nuestro diccionario de claves si existe, por ID, second es un booleano
    // Si la inserción falla (second == false), el ID ya existe
    if (!res.second) {
        throw ("Usuario duplicado" Usuario::Id_duplicado(id));
    }
}

Usuario::~Usuario(){
    // eliminamos todas sus tarjetas, antes de borrarlo
    typedef Usuario::Tarjetas::iterator IT_tar;
    for (IT_tar i = tarjetas_.begin(); i != tarjetas_.end(); i++){ //Usuario::Tarjetas::iterator it para modificar 
        (i->second).anular_titular();
    }
    // eliminamos el usuario de la lista correspondiente, unordered_set
    id_usuarios.erase(identificador_);
}

// Enlace de Tarjeta-Usuario

void Usuario::es_titular_de(Tarjeta& T){
    // hacemos la asociacion Usuario 1 --- N tarjetas
    if (*this->id() == (T.titular())->id()){ // this == T.titular(), mal pues no tenemos método operator==(), pues id es único
        tarjetas_.insert(std::make_pair(T.numero(), &T)); // creamos la asociacion, donde le metemos la clave numero, y la tarjeta T <Numero, Tarjeta*>
    }
}

void Usuario::no_es_titular(Tarjeta& T){
    // rompemos el enlace
    T.anular_titular();
    tarjetas_.erase(T.numero());
}

// Enlace de Artículo-Usuario

// Aqui podemos tanto introducir como borrar articulos
void Usuario::comprar(Articulo& A, size_t cant){
    // declaramos el tipo de iteradores solo dentro de esta función
    typedef Usuario::Articulos::iterator IT_art; // <Articulo*, size_t> == Articulos

    // verificamos si el contenedor unordered_map posee el artículo, si no solo actualizamos
    if (cant > 0){
        std::pair<IT_art, bool> res = articulos_.insert(std::make_pair(&A, cant));  // probamos si se inserto bien, guardando el valor en el pair

        if (!res.second){ 
            res.first->second += cant; // accedemos directamente dsd el iterador, pues desde la instancia del contenedor no se puede. HAY QUE ACCEDER CON UN ITERADOR
        }

    } else if (cant < 0) {
        // eliminamos los articulos (no distinguimos entre 0 o -INF (SIZE_NAX))
        IT_art it = articulos_.find(&A); // donde it apunta a cierto artículo del carrito

        // sino lo encontramos en el contenedor a la hacer find contenedor.end(), apunta despues del último elto (a nada vamos)
        if (it != articulos_.end()){
            // borramos todo, o eliminamos el objeto de la compra, o bien reducimos la cantidad
            if (it->second <= cant){
                articulos_.erase(&A);
            } else {
                it->second -= cant;
            }
        }
    } else {
        articulos_.erase(&A);
    }
}

// Operador de flujo de salida + otro método al for tradicional (parecido a python)
std::ostream& operator <<(std::ostream& os, const Usuario& user){
    os << user.id() << "[" << user.clave().operator const char*() <<  "]" << user.nombre() 
    << user.apellidos() << std::endl; // Recordamos que el operador de clave llama al operador de cadena que convierte explicitamente a un const char*

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

// RECORDAMOS LO SIGUIENTE: compra() llama a articulos, que es un contenedor std -> unordered_map<Articulo*, size_t>
void mostrar_carro(std::ostream& os, const Usuario& U){
    os << "Carrito de compra de" << U.id() << "[Articulos: " << U.n_articulos() << "] \n"
    << " Cant. Articulo" << std::endl;
    os << std::setw(95)<<std::setfill('=') << '' << std::endl; // formato deseado ========

    // Definimos el tipo de iterador
    typedef Usuario::Articulos::const_iterator IT_art;
    for (IT_art it = U.compra().begin(); it != U.compra().end(); it++){ // donde apunta es al contenedor, pues accedemos ahora directamente a él
        os << std::setw(4) << std::setfill(' ') << it->second 
           << "  [" << it->first->referencia() << "] "
           << "\"" << it->first->titulo() << "\", "
           << it->first->f_publi().año() << ". "
           << std::fixed << std::setprecision(2) 
           << it->first->precio() << " €"
           << std::endl;
    }
}