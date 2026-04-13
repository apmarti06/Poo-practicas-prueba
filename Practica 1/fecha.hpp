#ifndef FECHAS_H
#define FECHAS_H

#include <iosfwd>

class Fecha {
    public:
        
        //Fecha dada dd/mm/AA 
        explicit Fecha(int d = 0, int m = 0, int a = 0);
        
        //Constructor de copia fecha
        Fecha(const Fecha& A);
        
        //Constructor de conversion a partir de cadena de bajo nivel (dd/mm/aa)
        Fecha(const char* fecha);

        //Funciones observadoras

        inline int dia() const { return dia_; };
        inline int mes() const { return mes_; };
        inline int año() const { return año_; };

        //Miembros de la clase
        static const int AñoMinimo = 1902, AñoMaximo = 2037;
        
        //Sobrecarga de operadores
        Fecha& operator ++(); //Preincremento
        Fecha operator ++(int i); //Pos-incremento
        Fecha& operator --(); //Predecremento
        Fecha operator --(int i); //Posdecremento, usando i para decir el valor que poseia anterior mente

        Fecha& operator =(const Fecha& A);
        Fecha operator+(int i) const; // operador que no cambia (metodo const) (fecha + entero)
        Fecha& operator +=(int i);
        Fecha operator-(int i) const; // operador que no cambia (metodo const) (fecha + entero)
        Fecha &operator-=(int i);

        // Operador de conversion de un puntero char, lo modificamos por la practica 1
        //operator const char* () const;
        const char* cadena() const;

        // Sobrecargamos operadores de clase <<, >> y como no son miembros de la misma, los declaramos que son friend
        friend std::ostream& operator<<(std::ostream& os, const Fecha& f);
        friend std::istream& operator<<(std::istream& is, Fecha& f);

        // operadores de sobrecarga friend
        friend bool operator ==(const Fecha& A, const Fecha& B);
        friend bool operator >(const Fecha& A, const Fecha& B);
        friend bool operator <(const Fecha& A, const Fecha& B);
        friend bool operator <=(const Fecha& A, const Fecha& B);
        friend bool operator >=(const Fecha& A, const Fecha& B);
        friend bool operator !=(const Fecha& A, const Fecha& B);

        class Invalida {
            public:
                Invalida(const char* e) : error{e} {}
                inline const char* por_que() const { return error; }
            private:
                const char* error; 
        };

        //inline void mostrar() const { std::cout << dia_ << "/" << mes_ << "/" << año_; }

    private:
        int dia_, mes_, año_;
        // Usamos mutable para devolverlos en métodos constantes
        mutable char* crep;

        static bool descomponerFecha(const char* fechaFormateada, int &dia, int &mes , int &año);
        void validarFecha() const;
};


#endif