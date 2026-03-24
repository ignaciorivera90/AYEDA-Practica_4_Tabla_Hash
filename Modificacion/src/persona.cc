#include "persona.h"

Persona::Persona() : clave1_(""), clave2_(0), clave3_(""), nombre_(""), apellido1_(""), tfno_("") {}

Persona::Persona(const std::string& clave1, int clave2, const std::string& clave3, const std::string& nombre,
                 const std::string& apellido1, const std::string& tfno)
                : clave1_(clave1), clave2_(clave2), clave3_(clave3), nombre_(nombre), apellido1_(apellido1), tfno_(tfno) {}

bool Persona::operator==(const Persona& other) const {
  return ((clave1_ == other.clave1_) && (clave2_ == other.clave2_) && (clave3_ == other.clave3_));
}

bool Persona::operator!=(const Persona& other) const {
  return !(*this == other);
}

bool Persona::operator<(const Persona& other) const {
  return GetClave() < other.GetClave();
}

std::string Persona::GetClave() const {
  return clave1_ + std::to_string(clave2_) + clave3_;
}

Persona::operator long() const {
  std::string combined = GetClave();

  long value = 0;
  for (char c : combined) {
    value = value * 31 + static_cast<unsigned char>(c);
  }

  return value;
}

std::ostream& operator<<(std::ostream& os, const Persona& persona) {
  os << persona.GetClave();
  return os;
}

std::istream& operator>>(std::istream& is, Persona& persona) {
  std::cout << "\nClave1: ";
  is >> persona.clave1_;
  std::cout << "Clave2: ";
  is >> persona.clave2_;
  std::cout << "Clave3: ";
  is >> persona.clave3_;
  std::cout << "Nombre: ";
  is >> persona.nombre_;
  std::cout << "Apellido1: ";
  is >> persona.apellido1_;
  std::cout << "Telefono: ";
  is >> persona.tfno_;
  return is;
}

const std::string& Persona::GetClave1() const { return clave1_; }
int Persona::GetClave2() const { return clave2_; }
const std::string& Persona::GetClave3() const { return clave3_; }
const std::string& Persona::GetNombre() const { return nombre_; }
const std::string& Persona::GetApellido1() const { return apellido1_; }
const std::string& Persona::GetTfno() const { return tfno_; }