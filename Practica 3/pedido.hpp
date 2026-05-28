#include "fecha.hpp"
#include "tarjeta.hpp"
#include "usuario.hpp"

// clases de asociación
#include "usuario_pedido.hpp"
#include "pedido_articulo.hpp"

class Tarjeta;
class PedidoArticulo;
class UsuarioPedido;

class Pedido {
    public:
        // constructor de Pedido
        Pedido(UsuarioPedido& UP, PedidoArticulo& PA, Usuario& u, const Tarjeta& t, const Fecha& f);

        // Metodo consultoras
        inline int numero() const { return num_; }
        inline Fecha fecha() const { return fecha_; }
        inline const Tarjeta* tarjeta() const { return tarjeta_; }
        inline double total() const { return total_; }

        // evita crear un pedido vacío
        class Vacio {
            public:
                Vacio(Usuario* u) : user_{u} {}
                Usuario& usuario() const { return *user_; }
            private: 
                Usuario* user_;
        };

        // verifica si la tarjeta del titular pertenece al usuario
        class Impostor {
            public:
                Vacio(Usuario* u) : user_{u} {}
                Usuario& usuario() const { return *user_; }
            private: 
                Usuario* user_;
        };

        // Lanza dicha excepcion si no queda mas stock disponible de un articulo x
        class SinStock{
            public: 
                SinStock(Articulo* a) : articulo_{a} {}
                Articulo& articulo() const { return *articulo_; }
            private:
                Articulo* articulo_;
        };

    private:
        int num_;
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double total_;

        // Atributos estaticos de clase
        static int n_pedidos_;
};