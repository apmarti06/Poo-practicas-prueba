#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "usuario.hpp"
#include "fecha.hpp"
#include "numero.hpp"
#include <iostream>
#include <unordered_set>

// Forward declaration
class Usuario;

class Tarjeta {
public:
    typedef enum {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress} Tipo;
    
    // Constructor
    Tarjeta(const Numero&, Usuario&, const Fecha&);
    
    // Eliminar copia
    Tarjeta(const Tarjeta&) = delete;
    Tarjeta& operator=(const Tarjeta&) = delete;
    
    // Observadores
    const Numero& numero() const noexcept { return numero_; }
    const Usuario* titular() const noexcept { return titular_; }
    const Fecha& caducidad() const noexcept { return caducidad_; }
    bool activa() const noexcept { return activa_; }
    
    // Modificadores
    void activar() noexcept { activa_ = true; }
    void desactivar() noexcept { activa_ = false; }
    
    // Asociación bidireccional
    void es_titular_de(Usuario& t) noexcept;
    
    // Método que devuelve el tipo de tarjeta
    Tipo type() const noexcept;
    
    // Destructor
    ~Tarjeta();
    
    // Excepciones
    class Caducada {
        Fecha fecha_;
    public:
        Caducada(const Fecha& f) : fecha_(f) {}
        const Fecha& cuando() const noexcept { return fecha_; }
    };
    
    class Desactivada { // Nueva clase
        public:
            Desactivada(const Tarjeta& T) : tarjeta_{T} {}
            const Tarjeta& porque() const noexcept { return tarjeta; }
        private:
            Tarjeta tarjeta_;
    };

    class Num_Duplicado {
        Numero num_;
    public:
        Num_Duplicado(const Numero& n) : num_(n) {}
        const Numero& que() const noexcept { return num_; }
    };
    
    // Operadores amigos
    friend std::ostream& operator<<(std::ostream& os, const Tarjeta&);
    friend std::ostream& operator<<(std::ostream& os, Tipo tipo);
    friend bool operator<(const Tarjeta& a, const Tarjeta& b);

private:
    const Numero numero_;
    Usuario* titular_;  // No es const para poder modificarlo
    const Fecha caducidad_;
    bool activa_;
    
    static std::unordered_set<Numero> tarjetas_;
    
    friend class Usuario;
    void anular_titular() noexcept;
};

#endif