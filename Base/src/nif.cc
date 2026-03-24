#include "nif.h"

#include <cstdlib>
#include <ctime>

nif::nif() {
  static bool seeded = false;
  if (!seeded) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    seeded = true;
  }
  value_ = 10000000 + (std::rand() % 90000000);
}

nif::nif(long value) : value_(value) {}

nif::operator long() const {
  return value_;
}

bool nif::operator==(const nif& other) const {
  return value_ == other.value_;
}

bool nif::operator!=(const nif& other) const {
  return value_ != other.value_;
}

bool nif::operator<(const nif& other) const {
  return value_ < other.value_;
}

bool nif::operator>(const nif& other) const {
  return value_ > other.value_;
}

std::ostream& operator<<(std::ostream& os, const nif& n) {
  os << n.value_;
  return os;
}

std::istream& operator>>(std::istream& is, nif& n) {
  is >> n.value_;
  return is;
}