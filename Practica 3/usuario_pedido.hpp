#include "usuario.hpp"
#include "pedido.hpp"

#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

class UsuarioPedido {
    public:
        // diccionarios de la clase de asociación (bidireccional)

        // 1. diccionario de puntero Usuario a un conjunto de eltos (pedido)
        typedef std::set<Pedido*> Pedidos;
        typedef std::map<Usuario*, Pedidos> Usuario_Pedido;

        // 2. diccionario de puntero pedido a puntero usuario 
        typedef std::map<Pedido*, Usuario*> Pedido_Usuario;

        // Metodos de asociacion bidireccional
        void asocia(Usuario& u, Pedido& p);
        void asocia(Pedido& p, Usuario& u);

        // Metodos observadores, devolver los pedidos del usuario x, y de un pedido cual fue su usuario
        Pedidos pedidos(Usuario& U) const;
        Usuario* cliente(Pedido& p) const;

    private: 
    // contenedores de las claves a guardar y valores
        Usuario_Pedido usuario_pedido;
        Pedido_Usuario pedido_usuario;
};