#ifndef PERSONA_H_
#define PERSONA_H_

#include <iostream>
#include <string>

class Persona {
 public:
  Persona();
  Persona(const std::string& clave1, int clave2, const std::string& clave3,
          const std::string& nombre, const std::string& apellido1,
          const std::string& tfno);

  bool operator==(const Persona& other) const;
  bool operator!=(const Persona& other) const;
  bool operator<(const Persona& other) const;

  operator long() const;

  friend std::ostream& operator<<(std::ostream& os, const Persona& persona);
  friend std::istream& operator>>(std::istream& is, Persona& persona);

  const std::string& GetClave1() const;
  int GetClave2() const;
  const std::string& GetClave3() const;
  const std::string& GetNombre() const;
  const std::string& GetApellido1() const;
  const std::string& GetTfno() const;

  std::string GetClave() const;
    
 private:
  std::string clave1_;
  int clave2_;
  std::string clave3_;
  std::string nombre_;
  std::string apellido1_;
  std::string tfno_;
};

#endif