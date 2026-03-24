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
// Archivo dispersion.h: definición de las funciones de dispersión utilizadas
//                      en la tabla hash.

#ifndef DISPERSION_H_
#define DISPERSION_H_

#include <cstdlib>

template <class Key>
class DispersionFunction {
 public:
  virtual ~DispersionFunction() = default;
  virtual unsigned operator()(const Key&) const = 0;
};

template <class Key>
class ModuleDispersion : public DispersionFunction<Key> {
 public:
  explicit ModuleDispersion(unsigned table_size)
      : table_size_(table_size) {}

  unsigned operator()(const Key& key) const override {
    return static_cast<unsigned>(static_cast<long>(key) % table_size_);
  }

 private:
  unsigned table_size_;
};

template <class Key>
class SumDispersion : public DispersionFunction<Key> {
 public:
  explicit SumDispersion(unsigned table_size)
      : table_size_(table_size) {}

  unsigned operator()(const Key& key) const override {
    unsigned sum = 0;
    unsigned temp = static_cast<unsigned>(static_cast<long>(key));

    while (temp > 0) {
      sum += temp % 10;
      temp /= 10;
    }
    return sum % table_size_;
  }

 private:
  unsigned table_size_;
};

template <class Key>
class PseudoRandomDispersion : public DispersionFunction<Key> {
 public:
  explicit PseudoRandomDispersion(unsigned table_size)
      : table_size_(table_size) {}

  unsigned operator()(const Key& key) const override {
    std::srand(static_cast<unsigned>(static_cast<long>(key)));
    return std::rand() % table_size_;
  }

 private:
  unsigned table_size_;
};

#endif