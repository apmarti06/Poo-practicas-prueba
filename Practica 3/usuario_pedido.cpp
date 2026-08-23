#include "usuario_pedido.hpp"

void UsuarioPedido::asocia(Usuario& u, Pedido& p){
    // añadimos la referencia al diccionario, con insert pues se trata de un conjunto
    directa_[&u].insert(&p);
    // asignamos al pedido quien es el usuario , con una referencia pues guarda solo un único puntero
    inversa_[&p] = &u;
}

void UsuarioPedido::asocia(Pedido& p, Usuario& u){
    // usando la sobrecarga de operaciones hacemos uso de la otra funcion asocia de la clase
    asocia(u, p);
}

UsuarioPedido::Pedidos UsuarioPedido::pedidos(Usuario& u) const {
    // buscamos si existe el usuario deseado
    UsuarioPedido::Usuario_Pedido::const_iterator it = directa_.find(&u);

    // devolvemos la lista de pedidos si se ha encontrado
    if (it != usuario_pedido.end()){
        return it->second;
    } else { 
        UsuarioPedido::Usuario_Pedido pedido_vacio;
        return pedido_vacio; // o UsuarioPedido::Usuario_Pedido{}
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

    // significa al no haber ninguna clave, significa lo mismo, pues no hay más que un usuario por pedido
    return nullptr;
}