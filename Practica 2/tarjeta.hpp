#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "usuario.hpp"
#include "fecha.hpp"

// Para llamar a funciones de clases especificas para implementar miembros
class Usuario;  
class Tarjeta {
    public:

        typedef enum {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress} Tipo;
        Tarjeta(const Numero&, const Usuario&, const Fecha&);

        // Como para el usuario, decimos que no se puede crear copias de estas delegamos al operador de asignacion y su constructor de copia
        Tarjeta(const Tarjeta& otra) = delete;
        Tarjeta& operator=(const Tarjeta& otra) = delete;

        // Metodos de clase-miembros

        //Observadoras, donde usando const nos aseguramos que el objeto (realmente la instancia) que guarda es único y no compartido
        const Numero numero() const noexcept { return numero_; }
        const Usuario* titular() const noexcept { return titular_; }
        const Fecha caducidad() const noexcept { return caducidad_; }

        // Observadora - modificadora de tarjetas, sobrecargando activa
        bool activa() const noexcept {return activa_; }

        bool activa(bool estado) noexcept {
            activa_ = estado;
            return activa_;
        }

        // Método bidireccional entre Usuario-Tarjeta
        void es_titular_de(const Usuario& t) noexcept;

        // Método que devuelve que tipo de tarjeta es la que se esta utilizando MasterCard ...
        Tipo type() const noexcept;
        
        // Destructor
        ~Tarjeta();
        
        // Otra forma de implementar clases (ya que class son por defecto miembros privados)
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
            // clase vacia por el enunciado, pues llama al destructor de tarjeta, y no hace falta mas
        };
        
        // sobrecargamos el operador de extraccion de flujo
        friend std::ostream& operator <<(std::ostream& os, const Tarjeta&) noexcept;
        friend std::ostream& operator <<(std::ostream& os, const Tipo&) noexcept;
        friend bool operator <(const Tarjeta&, const Tarjeta&);

    private:
        const Numero numero_; // si desaparece la instancia (composicion)
        const Usuario* titular_; // no desaparece la instancia (agregacion), pues es el puntero entre Usuario-Tarjeta, pero no debe variar en el tiempo (es único)
        const Fecha caducidad_; // si desaparece la instancia (composicion)
        bool activa_;

        // Evitamos la duplicidad de tarjetas usando unordered_set donde nos aseguramos nosotros que no se repita
        static std::unordered_set<Numero> tarjetas_;

        // Hacemos que la clase usuario sea amiga para poder hacer uso
        // de funcion anular_titular, cuando se use su destructor
        friend class Usuario;
        void anular_titular();
};

#endif