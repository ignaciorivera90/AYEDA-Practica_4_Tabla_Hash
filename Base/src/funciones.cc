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
// Archivo funciones.cc: implementación de la función Usage para validar
//                      argumentos de entrada y mostrar ayuda.

#include "funciones.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "exceptions.h"

/**
 * @brief Validates command line arguments and shows help if requested.
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @throws MissingArgumentException if mandatory arguments are missing.
 */
void Usage(int argc, char* argv[]) {
  if (argc >= 2 && std::string(argv[1]) == "--help") {
    std::cout
        << "\nPráctica 4: Búsqueda por dispersión\n\n"
           "Modo de empleo:\n"
           "  ./Hashtable -ts <n> -fd <f> -hash <open|close> [-bs <n>] [-fe <f>]\n\n"
           "Parámetros obligatorios:\n"
           "  -ts <n>          Tamaño de la tabla (n > 0)\n"
           "  -fd <f>          Función de dispersión:\n"
           "                     1 = Módulo\n"
           "                     2 = Suma de dígitos\n"
           "                     3 = Pseudoaleatoria\n"
           "  -hash <modo>     Técnica de dispersión:\n"
           "                     open  = Dispersión abierta\n"
           "                     close = Dispersión cerrada\n\n"
           "Parámetros adicionales (solo cerrada):\n"
           "  -bs <n>          Tamaño del bloque (n > 0)\n"
           "  -fe <f>          Función de exploración:\n"
           "                     1 = Lineal\n"
           "                     2 = Cuadrática\n"
           "                     3 = Doble dispersión\n"
           "                     4 = Redispersión\n\n"
           "Ejemplos:\n"
           "  ./Hashtable -ts 10 -fd 1 -hash open\n"
           "  ./Hashtable -ts 10 -fd 2 -hash close -bs 2 -fe 1\n\n";

    std::exit(EXIT_SUCCESS);
  }

  if (argc < 7) {
    throw MissingArgumentException(
        "uso: ./Hashtable -ts <n> -fd <f> -hash <open|close> [-bs <n>] [-fe <f>]");
  }
}