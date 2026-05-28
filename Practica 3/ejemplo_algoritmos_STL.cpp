/* -*- mode: c++; compile-command: "g++ -std=c++17 -Wall -o ejemplo_algoSTL ejemplo_algoSTL.cpp" -*-
 * $Id: ejemplo_algoSTL.cpp 418 2018-04-27 19:12:54Z gerardo $
 *
 * Ejemplo de uso de un algoritmo que recibe un predicado unario (count_if),
 * donde se muestran las alternativas que hay para pasarle algo que se comporte
 * como un predicado.
 * También se ven otras cosas interesantes: contenedor y cómo inicializarlo,
 * iterador de flujo de salida, otros algoritmos, etc.
 * ©2014-2020 Gerardo
 * ©2026 Pedro
 */

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

inline bool mayor_q_7(int x) { return x > 7; } // Función para el 1er. caso

int main()
{
  // Contenedor e inicialización (C++11)
  std::vector<int> v { -32, 2, 1, 5, 7, 9, 3, 0, 4, 2, -32 };

  // ============================================================
  // IMPRESIÓN DEL VECTOR
  // ============================================================
  std::cout << "=====IMPRESIÓN DEL VECTOR=============\n"; 

  // 1- Con un bucle for «tradicional»
  std::cout << "Impresión con for tradicional........: v = {";
  for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) std::cout << ',';
    std::cout << ' ' << *it;
  }
  std::cout << " };\n";

  // 2- Range-for (C++11)
  std::cout << "Impresión con for de rango...........: v = { ";
  bool primero = true;
  for (int x : v) {
    if (!primero) std::cout << ", ";
    std::cout << x;
    primero = false;
  }
  std::cout << " };\n";

  // 3- copy + ostream_iterator
  std::cout << "Impresión con copy + ostream_iterator: v = { ";
  std::copy(v.begin(), v.end() - 1, std::ostream_iterator<int>(std::cout, ", "));
  std::cout << v.back() << " };\n";

  // 4- for_each + lambda
  std::cout << "Impresión con for_each + lambda......: v = { ";
  primero = true;
  std::for_each(v.begin(), v.end(), [&](int x) {
    if (!primero) std::cout << ", ";
    std::cout << x;
    primero = false;
  });
  std::cout << " };\n";


  // ============================================================
  // USO DE count_if CON DISTINTOS PREDICADOS
  // ============================================================
  std::cout << "\n======USO DE count_if ================\n";

  auto imprimir = [](int n, int c) {
    std::cout << "Hay " << n << " elemento"
              << (n == 1 ? " " : "s ")
              << (n == 1 ? "mayor" : "mayores")
              << " que " << c << '\n';
  };

  // 1- (Puntero a) función
  std::cout << "1- (Puntero a) función ..............: ";
  int n = std::count_if(v.begin(), v.end(), mayor_q_7); //El & antes de mayor_q_7 es opcional
  imprimir(n, 7);

  // 2- Con un objeto función, cuya clase se crea expresamente
  struct MayorQue7 {
    bool operator()(int x) const { return x > 7; }
  };

  std::cout << "2- Objeto función simple.............: ";
  n = std::count_if(v.begin(), v.end(), MayorQue7{});
  imprimir(n, 7);

  // 3- Objeto función con estado
  struct MayorQue {
    int limite;
    bool operator()(int x) const { return x > limite; }
  };

  std::cout << "3- Objeto función con estado.........: ";
  n = std::count_if(v.begin(), v.end(), MayorQue{3});
  imprimir(n, 3);

  // 4- Función anónima (lambda) 
  std::cout << "4- Lambda............................: ";
  n = std::count_if(v.begin(), v.end(), [](int x) {
    return x > 0;
  });
  imprimir(n, 0);

  // 5- Lambda con captura (equivalente a objeto función con estado)
  std::cout << "5- Lambda con captura................: ";
  int limite = 5;
  n = std::count_if(v.begin(), v.end(), [limite](int x) {
    return x > limite;
  });
  imprimir(n, limite);
}