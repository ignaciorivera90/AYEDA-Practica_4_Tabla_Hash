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
// Archivo nif.cc: implementación de la clase nif que representa la clave
//                 utilizada en la tabla hash.

#include "nif.h"

#include <cstdlib>
#include <ctime>

/**
 * @brief Default constructor. Generates a random 8-digit NIF.
 *
 * @details
 * Initializes the random seed only once and generates a number
 * between 10000000 and 99999999.
 */
nif::nif() {
  static bool seeded = false;
  if (!seeded) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    seeded = true;
  }
  value_ = 10000000 + (std::rand() % 90000000);
}

/**
 * @brief Constructor from a long value.
 * @param value Numeric value of the NIF.
 */
nif::nif(long value) : value_(value) {}

/**
 * @brief Conversion operator to long.
 * @return The numeric value of the NIF.
 */
nif::operator long() const {
  return value_;
}

/**
 * @brief Equality operator.
 * @param other Another nif to compare.
 * @return true if both values are equal, false otherwise.
 */
bool nif::operator==(const nif& other) const {
  return value_ == other.value_;
}

/**
 * @brief Inequality operator.
 * @param other Another nif to compare.
 * @return true if values are different, false otherwise.
 */
bool nif::operator!=(const nif& other) const {
  return value_ != other.value_;
}

/**
 * @brief Less-than operator.
 * @param other Another nif to compare.
 * @return true if this value is less than other.
 */
bool nif::operator<(const nif& other) const {
  return value_ < other.value_;
}

/**
 * @brief Greater-than operator.
 * @param other Another nif to compare.
 * @return true if this value is greater than other.
 */
bool nif::operator>(const nif& other) const {
  return value_ > other.value_;
}

/**
 * @brief Output stream operator.
 * @param os Output stream.
 * @param n nif to print.
 * @return Reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const nif& n) {
  os << n.value_;
  return os;
}

/**
 * @brief Input stream operator.
 * @param is Input stream.
 * @param n nif to read.
 * @return Reference to the input stream.
 */
std::istream& operator>>(std::istream& is, nif& n) {
  is >> n.value_;
  return is;
}