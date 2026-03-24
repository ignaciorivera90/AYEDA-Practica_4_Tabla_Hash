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
// Archivo main.cc: punto de entrada del programa que inicializa el simulador
//                  y gestiona el control de excepciones.

#include <iostream>

#include "exceptions.h"
#include "simulator.h"
#include "funciones.h"

/**
 * @brief Main entry point of the application.
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @return 0 if execution finishes correctly, 1 otherwise.
 *
 * @details
 * This function:
 *  - Validates input arguments using Usage().
 *  - Creates the Simulator object.
 *  - Executes the interactive menu.
 *  - Handles both custom and standard exceptions.
 */
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