#include <ctime>
#include <iostream>
#include <iomanip>
#include <cstdio> //Para hacer uso de sscanf
#include <cmath>    //Para hacer uso de log y pow
#include <utility>  //Para usar std::swap
#include "./fecha.hpp"
#include "fecha.hpp"

//Metodos privados

bool Fecha::descomponerFecha(const char* fechaFormateada, int &dia, int &mes , int &año) {
    bool correcto = std::sscanf(fechaFormateada, "%d/%d/%d", &dia, &mes, &año) == 3;
    if(correcto && año > 0) {
        int cifras = log10(año) + 1;
        if (cifras > 4) año /= pow(10, cifras - 4);
    }
    return correcto && ((año % 4 == 0 && año % 100 != 0) || año % 400 == 0);
}

void Fecha::validarFecha() const  {
    // verificamos si el mes y año es correcto
    if(año_ > Fecha::AñoMaximo || año_ < Fecha::AñoMinimo) {
        throw Fecha::Invalida("Año invalido. \n");
    } else if (mes_ < 1 || mes_ > 12) {   
        throw Fecha::Invalida("Mes invalido. \n");
    }

    std::tm tm = {};

    tm.tm_mday = dia_;
    tm.tm_mon = mes_ - 1;
    tm.tm_year = año_ - 1900;

    std::mktime(&tm); //Normalizamos la fecha tm 

    if(dia_ != tm.tm_mday || mes_ != tm.tm_mon + 1 || año_ != tm.tm_year + 1900) {
        throw Fecha::Invalida("La fecha introducida no existe. \n");
    }
}

//Funciones públicas
Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), año_(a){    
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm* tiempo_desglosado = std::localtime(&tiempo_actual);
    if(d == 0) { dia_ = tiempo_desglosado->tm_mday; }
    if(m == 0) { mes_ = tiempo_desglosado->tm_mon + 1; }
    if(a == 0) { año_ = tiempo_desglosado->tm_year + 1900; }
    validarFecha();
}

//Constructor de copia
Fecha::Fecha(const Fecha& A) : Fecha(A.dia_, A.mes_, A.año_) {}

//Constructor de conversión de cadena de bajo nivel (dd/mm/aa)
Fecha::Fecha(const char* fecha) {
    int d, m, a;

    if(!descomponerFecha(fecha, d, m, a)) {
        throw Fecha::Invalida("No se ha pasado el formato correcto de cadena. \n");
    }

    Fecha fechaNueva(d, m, a);

    dia_ = fechaNueva.dia();
    mes_ = fechaNueva.mes();
    año_ = fechaNueva.año();
}

//Operador de asignación + sobrecarga de operadores

Fecha& Fecha::operator =(const Fecha& A) {
    Fecha copia(A);

    std::swap(dia_, copia.dia_);
    std::swap(mes_, copia.mes_);
    std::swap(año_, copia.año_);

    return *this;
}

// apartir de este operador creamos el resto

Fecha& Fecha::operator +=(int i){
    std::tm fechaNormalizada = {};

    fechaNormalizada.tm_mday = dia_ + i;
    fechaNormalizada.tm_mon = mes_ - 1;
    fechaNormalizada.tm_year = año_ - 1900;

    std::mktime(&fechaNormalizada); // Normalizamos la fecha

    dia_ = fechaNormalizada.tm_mday;
    mes_ = fechaNormalizada.tm_mon + 1;
    año_ = fechaNormalizada.tm_year + 1900;

    validarFecha(); 
    return *this; // devolvemos la fecha resultante
}

bool operator ==(const Fecha& A, const Fecha& B) {
    return (A.dia_ == B.dia_) && (A.mes_ == B.mes_) && (A.año_ == B.año_);
}

bool operator >(const Fecha& A, const Fecha& B) {
    if(A.año_ != B.año_) {
        return A.año_ > B.año_;
    } else if(A.mes_ != B.mes_) {
        return A.mes_ > B.mes_;
    } else {
        return A.dia_ > B.dia_;
    }
}

bool operator <(const Fecha& A, const Fecha& B) {
    return !(A > B) && !(A == B);
}

bool operator <=(const Fecha& A, const Fecha& B) {
    return !(A > B);
}

bool operator >=(const Fecha& A, const Fecha& B) {
    return !(A < B);
}

bool operator !=(const Fecha& A, const Fecha& B) {
    return !(A == B);
}

// Operadores que usamos copias del objeto para calcular fechas, (metodos const)

Fecha Fecha::operator +(int i) const{
    Fecha copia;
    copia = *this;

    // utilizamos la sobrecarga de operadores
    copia += i;
    return copia;
}

Fecha Fecha::operator -(int i) const {
    Fecha copia;
    copia = *this;
    // utilizamos la sobrecarga de operadores
    copia += -i;
    return copia;
}


// Métodos que devolvemos objetos donde se alteran 
Fecha& Fecha::operator-=(int i){ // 
    return *this += -i;
}

// Preincremento devuelve el objeto modificado  
Fecha& Fecha::operator ++(){ // Preincremento
    return *this += 1;
}

// Preincremento devuelve el objeto modificado
Fecha& Fecha::operator --(){ // Preincremento
    return *this += 1;
}

// Postincremento devuelve el objeto dandole el valor al deseado, y luego realiza el incremento
Fecha Fecha::operator++(int i){
    Fecha copia(*this);
    *this += 1;
    return copia;
}

// Postincremento devuelve el objeto con el valor deseado y luego realiza el decremento
Fecha Fecha::operator--(int i){
    Fecha copia(*this);
    *this += -1;
    return copia;
}

// PRACTICA 1
const char* Fecha::cadena () const // definimos antes operator const char* operator (operador de conversion)
{
    // Rellenamos para saber que sea el dia de la semana
    std::tm fechaNormalizada = {};

    fechaNormalizada.tm_mday = dia_;
    fechaNormalizada.tm_mon = mes_ - 1;
    fechaNormalizada.tm_year = año_ - 1900;
    
    std::mktime(&fechaNormalizada);

    // Array con los dias de la semana y nombre de meses
    const char* dias_sem[] {
        "lunes", "martes", "miercoles", "jueves", "viernes", "sabado", "domingo"
    };

    const char* mes_nom[] {
        "enero" , "febrero", "marzo", "abril", "mayo", "junio", "julio",
         "agosto", "septiembre", "octubre", "noviembre", "diciembre"
    };

    // Formatear en crep (te guarda la cadena no traducida)
    std::sprintf(crep, "%s %d de %s de %d", dias_sem[fechaNormalizada.tm_mday], dia_, mes_nom[fechaNormalizada.tm_mon], año_);
    return crep;
}

// Flujo de extraccion
std::ostream& operator<<(std::ostream& os, const Fecha& f)
{
    os << f.cadena();
    return os;
}

// Flujo de inserción convirtiendo una cadena de bajo nivel a una fecha 
std::istream& operator>>(std::istream& is, Fecha& f)
{
    char buffer[11];

    is >> std::setw(11) >> buffer;

    if (!is) {
        return is;
    }

    try {
        Fecha aux(buffer);
        f = aux;
    }
    catch (const Fecha::Invalida&) {
        is.setstate(std::ios::failbit);
        throw;
    }

    return is;
}


// main std::cout << i;