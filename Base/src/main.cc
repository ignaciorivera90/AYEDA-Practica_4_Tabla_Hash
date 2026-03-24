// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
//
// Autor: Ignacio Andres Rivera Barrientos
// Fecha: 24/03/2026
// Archivo main.cc: programa principal.

#include <iostream>

#include "exceptions.h"
#include "simulator.h"
#include "funciones.h"

int main(int argc, char* argv[]) {
  try {
    Usage(argc, argv);

    Simulator simulator(argc, argv);
    simulator.Run();

  } catch (const Exception& exception) {
    std::cerr << "Excepcion: " << exception.what() << '\n';
    return 1;
  } catch (const std::exception& exception) {
    std::cerr << "Error inesperado: " << exception.what() << '\n';
    return 1;
  }

  return 0;
}