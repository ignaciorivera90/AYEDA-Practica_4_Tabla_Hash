#include "funciones.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "exceptions.h"

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