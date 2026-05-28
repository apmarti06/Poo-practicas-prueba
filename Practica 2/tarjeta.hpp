#include "usuario.hpp"
#include "fecha.hpp"

#ifndef TARJETA_HPP
#define TARJETA_HPP

// para poder hacer las asociaciones directas, al tener un puntero a Usuario
class Usuario;  

class Tarjeta {
    public:

        typedef enum {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress} Tipo;
        Tarjeta(const Numero&, Usuario&, const Fecha&);

        // Como para el usuario, decimos que no se puede crear copias de estas delegamos al operador de asignacion y su constructor de copia
        Tarjeta(const Tarjeta& otra) = delete;
        Tarjeta& operator=(const Tarjeta& otra) = delete;

        // Metodos de clase-miembros

        //Observadoras
        const Numero numero() const noexcept { return numero_; }
        const Usuario* titular() const noexcept { return titular_; }
        const Fecha caducidad() const noexcept { return caducidad_; }

        // Observadora - modificadora de tarjetas
        bool activa() const noexcept {return activa; }

        bool activa(bool estado) noexcept {
            activa = estado;
            return activa;
        }

        void es_titular_de(Usuario& t) noexcept;

        Tipo tipo() const noexcept;
        
        // Destructor
        ~Tarjeta();
        
        class Caducada {
            Fecha fecha_;
            public:
                Caducada(const Fecha& f) : fecha_(f) {}
                const Fecha& cuando() noexcept {return fecha_; }
        };

        class Num_Duplicado {
            Numero num_;
            public:
                Num_Duplicado(const Numero& n) : num_{n} {}
                const Numero& que() noexcept {return num_; }
        };

        // Nueva clase practica 3
        class Desactivada {
            // clase vacia por el enunciado
        };
        
        friend std::ostream& operator <<(std::ostream& os, const Tarjeta&) noexcept;
        friend std::ostream& operator <<(std::ostream& os, const Tipo&) noexcept;
        friend bool operator <(const Tarjeta&, const Tarjeta&);

    private:
        const Numero numero_;
        const Usuario* titular_;
        const Fecha caducidad_;
        bool activa;

        // Evitamos la duplicidad de tarjetas usando unordered_set, su conjunto de estas ya ordenadas
        static std::unordered_set<Numero> tarjetas_;

        // Hacemos que la clase usuario sea amiga para poder hacer uso
        // de funcion anular_titular, cuando se use su destructor
        friend class Usuario;
        void anular_titular();
};

#endif