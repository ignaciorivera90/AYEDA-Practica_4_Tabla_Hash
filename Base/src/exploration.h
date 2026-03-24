#ifndef EXPLORATION_H_
#define EXPLORATION_H_

#include <cstdlib>
#include "dispersion.h"

template <class Key>
class ExplorationFunction {
 public:
  virtual ~ExplorationFunction() = default;
  virtual unsigned operator()(const Key&, unsigned) const = 0;
};

template <class Key>
class LinearExploration : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key&, unsigned i) const override {
    return i;
  }
};

template <class Key>
class QuadraticExploration : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key&, unsigned i) const override {
    return i * i;
  }
};

template <class Key>
class DoubleDispersionExploration : public ExplorationFunction<Key> {
 public:
  explicit DoubleDispersionExploration(const DispersionFunction<Key>& fd)
      : fd_(fd) {}

  unsigned operator()(const Key& key, unsigned i) const override {
    unsigned step = fd_(key);
    if (step == 0) step = 1;
    return step * i;
  }

 private:
  const DispersionFunction<Key>& fd_;
};

template <class Key>
class RedispersionExploration : public ExplorationFunction<Key> {
 public:
  explicit RedispersionExploration(unsigned table_size)
      : table_size_(table_size) {}

  unsigned operator()(const Key& key, unsigned i) const override {
    std::srand(static_cast<unsigned>(static_cast<long>(key)));
    unsigned value = 0;
    for (unsigned j = 0; j < i; ++j) {
      value = std::rand();
    }
    return (value % (table_size_ - 1)) + 1;
  }

 private:
  unsigned table_size_;
};

#endif