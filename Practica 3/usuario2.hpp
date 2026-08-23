#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

#include "C:\Users\Usuario\c++\poo\Practica 0 y 1\cadena.hpp"
#include "C:\Users\Usuario\c++\poo\Practica 2\clave.hpp"
#include "C:\Users\Usuario\c++\poo\Practica 2\articulo.hpp"
#include "C:\Users\Usuario\c++\poo\Practica 2\numero.hpp"

class Tarjeta;

class Usuario {
public:
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, size_t> Articulos;

    // Constructor
    Usuario(Cadena id, Cadena n, Cadena ap, Cadena dir, Clave c);
    
    // Eliminar copia
    Usuario(const Usuario&) = delete;
    Usuario& operator=(const Usuario&) = delete;
    
    // Observadores
    Cadena id() const noexcept { return identificador_; }
    Cadena nombre() const noexcept { return nom_; }
    Cadena apellidos() const noexcept { return apell_; }
    Cadena direccion() const noexcept { return direccion_; }
    Clave clave() const noexcept { return clave_; }
    
    // Consultores (devuelven const para no modificar)
    const Tarjetas& tarjetas() const noexcept { return tarjetas_; }
    const Articulos& compra() const noexcept { return articulos_; }
    
    // Asociaciones con Tarjeta
    void es_titular_de(Tarjeta& t);
    void no_es_titular(Tarjeta& t);
    
    // Asociaciones con Artículo
    void comprar(Articulo& a, size_t cant = 1);
    
    void vaciar_carro() noexcept { articulos_.clear(); }
    size_t n_articulos() const noexcept { return articulos_.size(); }
    
    ~Usuario();
    
    // Excepción
    class Id_duplicado {
    public:
        Id_duplicado(const Cadena& c) : id_(c) {}
        const Cadena& idd() const { return id_; }
    private:
        Cadena id_;
    };
    
    friend std::ostream& operator<<(std::ostream& os, const Usuario& u);

private:
    const Cadena identificador_, nom_, apell_, direccion_;
    Clave clave_;
    
    Tarjetas tarjetas_;
    Articulos articulos_;
    
    static std::unordered_set<Cadena> id_usuarios;
};

void mostrar_carro(std::ostream& os, const Usuario& u);

#endif