// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 4: Implementación de la tabla hash
//
// Autor: Ignacio Andres Rivera Barrientos
// Correo: alu0101675053@ull.edu.es
// Fecha: 24/03/2026
// Archivo nif.h: declaración de la clase nif que representa la clave
//                utilizada en la tabla hash.

#ifndef NIF_H_
#define NIF_H_

#include <iostream>

class nif {
 public:
  nif();
  explicit nif(long);

  operator long() const;

  bool operator==(const nif&) const;
  bool operator!=(const nif&) const;
  bool operator<(const nif&) const;
  bool operator>(const nif&) const;

  friend std::ostream& operator<<(std::ostream&, const nif&);
  friend std::istream& operator>>(std::istream&, nif&);

 private:
  long value_;
};

#endif