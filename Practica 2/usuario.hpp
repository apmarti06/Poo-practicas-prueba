#include <map>
#include <set>

#include "cadena.hpp"
#include "clave.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "numero.hpp"

#ifndef USUARIO_HPP
#define USUARIO_HPP

class Usuario {
    public:
        // creamos los diccionarios a usar adelantando los nombres tarjetas_pago y carritos, asociacion clave-valor
        typedef std::map<Numero, Tarjeta*> Tarjetas;
        typedef std::unordered_map<Articulo*, size_t> Articulos;

        // Hacemos las operaciones que requiere la implementacion, por lo delegamos a no tanto al operador de asignacion y constructor de copia
        Usuario(Cadena id, Cadena n, Cadena ap, Cadena dir, Clave c);

        // Para evitar la duplicidad de Usuarios
        Usuario(const Usuario&) = delete;
        Usuario& operator=(const Usuario&) = delete;

        // Metodos-miembros

        // Consultoras normales
        inline Cadena id() const noexcept{return identificador_; }
        inline Cadena nombre() const noexcept{return nom_; }
        inline Cadena apellidos() const noexcept{return apell_; }
        inline Cadena direccion() const noexcept{return direccion_; }
        inline Clave clave() const noexcept {return clave_; }
        
        // Consultoras especiales
        inline Tarjetas tarjetas() {return tarjetas_; }
        inline Articulos compra() {return articulos_; }

        // Enlaces-Asociaciones de clases Tarjetas-Articulos
        void es_titular_de(Tarjeta&);
        void no_es_titular(Tarjeta&);
        void comprar(Articulo& A, size_t cant = 1);
        
        // al ser un contenedor, hacemos uso de las operaciones size, max_size, swap, clear, push_back
        inline void vaciar_carro() noexcept {articulos_.clear(); } 
        inline size_t n_articulos() noexcept const { return articulos_.size(); }

        // Destructor
        ~Usuario();

        class Id_duplicado {
            public:
                Id_duplicado(const Cadena& c) : id_{c} {}
                const Cadena& idd() const { return id_; }
            private:
                Cadena id_;
        };
        
        // Operador de insercion de flujo
        friend std::ostream& operator <<(std::ostream& os, const Usuario&);

    private:
        const Cadena identificador_, nom_, apell_, direccion_;  // atributos no modificables

        Clave clave_; // clave composicion, se borra implicitamente con la clase (reglas de composicion)

        // Usamos las claves, de los maps
        Tarjetas tarjetas_; // clave numero y valor tarjeta de credito (un unico valor por clave)
        Articulos articulos_; // clave articulo y la cantidad de articulos (size_t), asociacion con atributo de enlace

        // Conjunto de usuarios no repetidos
        static std::unordered_set<Cadena> id_usuarios_;
};

// Funcion externa, que imprima el flujo de salida
void mostrar_carro(std::ostream& os, const Usuario& U);

#endif