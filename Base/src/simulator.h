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
// Archivo simulator.h: declaración de la clase Simulator encargada de
//                      procesar argumentos, construir la tabla hash y
//                      gestionar el menú interactivo del programa.

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <string>

#include "dispersion.h"
#include "exceptions.h"
#include "exploration.h"
#include "hash_table.h"
#include "nif.h"
#include "sequence.h"

class Simulator {
 public:
  Simulator(int argc, char* argv[]);
  ~Simulator();

  void Run();

 private:
  void ParseArguments(int argc, char* argv[]);
  void BuildHashTable();
  void ShowMenu() const;
  void ClearScreen() const;
  void Pause() const;
  void PrintHeader() const;
  void HandleInsert();
  void HandleSearch();
  void HandlePrint() const;

  unsigned table_size_;
  unsigned block_size_;
  int fd_code_;
  int fe_code_;
  std::string hash_type_;

  DispersionFunction<nif>* fd_;
  ExplorationFunction<nif>* fe_;
  Sequence<nif>* hash_table_;
};

#endif