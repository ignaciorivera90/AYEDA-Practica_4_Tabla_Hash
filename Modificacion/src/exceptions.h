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
// Archivo exceptions.h: definición de las clases de excepción utilizadas
//                      para el control de errores en la aplicación.

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <stdexcept>
#include <string>

class Exception : public std::runtime_error {
 public:
  explicit Exception(const std::string& message)
      : std::runtime_error(message) {}
};

class MissingArgumentException : public Exception {
 public:
  explicit MissingArgumentException(const std::string& message)
      : Exception("MissingArgumentException: " + message) {}
};

class InvalidArgumentException : public Exception {
 public:
  explicit InvalidArgumentException(const std::string& message)
      : Exception("InvalidArgumentException: " + message) {}
};

class InvalidOptionException : public Exception {
 public:
  explicit InvalidOptionException(const std::string& message)
      : Exception("InvalidOptionException: " + message) {}
};

#endif