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