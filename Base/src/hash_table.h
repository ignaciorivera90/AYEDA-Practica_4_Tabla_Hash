#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <vector>
#include <iostream>

#include "dispersion.h"
#include "exploration.h"
#include "sequence.h"

template <class Key, class Container = staticSequence<Key>>
class HashTable : public Sequence<Key> {
 public:
  HashTable(unsigned table_size,
            DispersionFunction<Key>& fd,
            ExplorationFunction<Key>& fe,
            unsigned block_size)
      : table_size_(table_size),
        fd_(fd),
        fe_(fe),
        block_size_(block_size) {

    table_.resize(table_size_);
    for (unsigned i = 0; i < table_size_; ++i) {
      table_[i] = new Container(block_size_);
    }
  }

  ~HashTable() override {
    for (auto b : table_) delete b;
  }

  bool search(const Key& key) const override {
    unsigned base = fd_(key);

    for (unsigned i = 0; i < table_size_; ++i) {
      unsigned pos = (base + fe_(key, i)) % table_size_;
      if (table_[pos]->search(key)) return true;
    }
    return false;
  }

  bool insert(const Key& key) override {
    if (search(key)) return false;

    unsigned base = fd_(key);

    for (unsigned i = 0; i < table_size_; ++i) {
      unsigned pos = (base + fe_(key, i)) % table_size_;
      if (table_[pos]->insert(key)) return true;
    }
    return false;
  }

  void print(std::ostream& os) const override {
    for (unsigned i = 0; i < table_size_; ++i) {
      os << "[" << i << "] ";
      table_[i]->print(os);
      os << "\n";
    }
  }

 private:
  unsigned table_size_;
  std::vector<Container*> table_;
  DispersionFunction<Key>& fd_;
  ExplorationFunction<Key>& fe_;
  unsigned block_size_;
};


// 🔹 Especialización para dispersión abierta

template <class Key>
class HashTable<Key, dynamicSequence<Key>> : public Sequence<Key> {
 public:
  HashTable(unsigned table_size, DispersionFunction<Key>& fd)
      : table_size_(table_size), fd_(fd) {

    table_.resize(table_size_);
    for (unsigned i = 0; i < table_size_; ++i) {
      table_[i] = new dynamicSequence<Key>();
    }
  }

  ~HashTable() override {
    for (auto b : table_) delete b;
  }

  bool search(const Key& key) const override {
    unsigned pos = fd_(key) % table_size_;
    return table_[pos]->search(key);
  }

  bool insert(const Key& key) override {
    unsigned pos = fd_(key) % table_size_;
    return table_[pos]->insert(key);
  }

  void print(std::ostream& os) const override {
    for (unsigned i = 0; i < table_size_; ++i) {
      os << "[" << i << "] ";
      table_[i]->print(os);
      os << "\n";
    }
  }

 private:
  unsigned table_size_;
  std::vector<dynamicSequence<Key>*> table_;
  DispersionFunction<Key>& fd_;
};

#endif