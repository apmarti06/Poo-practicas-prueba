#include "usuario_pedido.hpp"

void UsuarioPedido::asocia(Usuario& u, Pedido& p){
    // añadimos la referencia al diccionario 
    usuario_pedido[&u].insert(&p);
    // asignamos al pedido quien es el usuario 
    pedido_usuario[&p] = &u;
}

void UsuarioPedido::asocia(Pedido& p, Usuario& u){
    // usando la sobrecarga de operaciones hacemos uso de la otra funcion asocia de la clase
    asocia(u, p);
}

UsuarioPedido::Pedidos UsuarioPedido::pedidos(Usuario& U) const {
    // buscamos si existe el usuario deseado
    UsuarioPedido::Usuario_Pedido::const_iterator it = usuario_pedido.find(&u);

    // devolvemos la lista de pedidos si se ha encontrado
    if (it != usuario_pedido.end()){
        return it->second;
    } else {
        UsuarioPedido::Usuario_Pedido pedido_vacio;
        return pedido_vacio;
    }
}

// comprobamos ya que al existir un operador modificador [], puedo sufrir cambios
UsuarioPedido::Usuario* UsuarioPedido::cliente(Pedido& p) const{
    // relacion unaria 
    Usuario_Pedido::const_iterator it = pedido_usuario.find(&p);

    // devolvemos un puntero del usuario si existe
    if (it != pedido_usuario.end()){
        return it->second;
    }

    // significa al no haber ninguna clave, significa lo mimsmo
    return nullptr;
}