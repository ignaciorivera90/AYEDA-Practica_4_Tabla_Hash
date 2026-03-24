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
// Archivo sequence.h: definición de las clases Sequence, dynamicSequence y
//                    staticSequence que representan los contenedores de
//                    almacenamiento de claves en la tabla hash.

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include <list>
#include <vector>
#include <iostream>

template <class Key>
class Sequence {
 public:
  virtual ~Sequence() = default;
  virtual bool search(const Key&) const = 0;
  virtual bool insert(const Key&) = 0;
  virtual void print(std::ostream&) const = 0;
};

template <class Key>
class dynamicSequence : public Sequence<Key> {
 public:
  bool search(const Key& key) const override {
    for (const auto& elem : data_) {
      if (elem == key) return true;
    }
    return false;
  }

  bool insert(const Key& key) override {
    if (search(key)) return false;
    data_.push_back(key);
    return true;
  }

  void print(std::ostream& os) const override {
    os << "[ ";
    for (const auto& e : data_) os << e << " ";
    os << "]";
  }

 private:
  std::list<Key> data_;
};

template <class Key>
class staticSequence : public Sequence<Key> {
 public:
  explicit staticSequence(unsigned block_size)
      : block_size_(block_size) {}

  bool search(const Key& key) const override {
    for (const auto& elem : data_) {
      if (elem == key) return true;
    }
    return false;
  }

  bool insert(const Key& key) override {
    if (search(key)) return false;
    if (isFull()) return false;
    data_.push_back(key);
    return true;
  }

  bool isFull() const {
    return data_.size() >= block_size_;
  }

  void print(std::ostream& os) const override {
    os << "[ ";
    for (const auto& e : data_) os << e << " ";
    for (unsigned i = data_.size(); i < block_size_; ++i) os << "- ";
    os << "]";
  }

 private:
  unsigned block_size_;
  std::vector<Key> data_;
};

#endif