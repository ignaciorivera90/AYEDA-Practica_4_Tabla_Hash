#include <cstdlib>
#include <iostream>
#include <string>

#include "dispersion.h"
#include "exploration.h"
#include "hash_table.h"
#include "nif.h"

void Usage(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0]
              << " -ts <s> -fd <module|sum|pseudorandom> "
              << "-hash <open|close> "
              << "[-bs <s> -fe <linear|quadratic|double-dispersion|redispersion>]\n";
    std::exit(EXIT_FAILURE);
  }

  if (std::string(argv[1]) == "--help") {
    std::cout << "Práctica 4: Búsqueda por dispersión\n\n";
    std::cout << "Uso:\n";
    std::cout << "  " << argv[0]
              << " -ts <s> -fd <module|sum|pseudorandom> "
              << "-hash <open|close> "
              << "[-bs <s> -fe <linear|quadratic|double-dispersion|redispersion>]\n\n";
    std::cout << "Opciones:\n";
    std::cout << "  -ts <s>   Tamaño de la tabla\n";
    std::cout << "  -fd <f>   Función de dispersión\n";
    std::cout << "  -hash     open o close\n";
    std::cout << "  -bs <s>   Tamaño del bloque (solo close)\n";
    std::cout << "  -fe <f>   Función de exploración (solo close)\n";
    std::exit(EXIT_SUCCESS);
  }
}

void ProcessArguments(int argc, char* argv[],
                      unsigned& tableSize,
                      std::string& fdCode,
                      std::string& hashType,
                      unsigned& blockSize,
                      std::string& feCode) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-ts" && i + 1 < argc) {
      tableSize = std::stoul(argv[++i]);
    } else if (arg == "-fd" && i + 1 < argc) {
      fdCode = argv[++i];
    } else if (arg == "-hash" && i + 1 < argc) {
      hashType = argv[++i];
    } else if (arg == "-bs" && i + 1 < argc) {
      blockSize = std::stoul(argv[++i]);
    } else if (arg == "-fe" && i + 1 < argc) {
      feCode = argv[++i];
    }
  }
}

int main(int argc, char* argv[]) {
  Usage(argc, argv);

  unsigned tableSize = 0;
  unsigned blockSize = 0;
  std::string fdCode;
  std::string hashType;
  std::string feCode;

  ProcessArguments(argc, argv, tableSize, fdCode, hashType, blockSize, feCode);

  if (tableSize == 0 || fdCode.empty() || hashType.empty()) {
    std::cerr << "Error: faltan argumentos obligatorios.\n";
    return EXIT_FAILURE;
  }

  DispersionFunction<nif>* fd = nullptr;

  if (fdCode == "module") {
    fd = new ModuleDispersion<nif>(tableSize);
  } else if (fdCode == "sum") {
    fd = new SumDispersion<nif>(tableSize);
  } else if (fdCode == "pseudorandom") {
    fd = new PseudoRandomDispersion<nif>(tableSize);
  } else {
    std::cerr << "Error: función de dispersión no válida.\n";
    return EXIT_FAILURE;
  }

  Sequence<nif>* table = nullptr;
  ExplorationFunction<nif>* fe = nullptr;

  if (hashType == "open") {
    table = new HashTable<nif, dynamicSequence<nif>>(tableSize, *fd);
  } else if (hashType == "close") {
    if (blockSize == 0 || feCode.empty()) {
      std::cerr << "Error: en dispersión cerrada debes indicar -bs y -fe.\n";
      delete fd;
      return EXIT_FAILURE;
    }

    if (feCode == "linear") {
      fe = new LinearExploration<nif>();
    } else if (feCode == "quadratic") {
      fe = new QuadraticExploration<nif>();
    } else if (feCode == "double-dispersion") {
      fe = new DoubleDispersionExploration<nif>(*fd);
    } else if (feCode == "redispersion") {
      fe = new RedispersionExploration<nif>(tableSize);
    } else {
      std::cerr << "Error: función de exploración no válida.\n";
      delete fd;
      return EXIT_FAILURE;
    }

    table = new HashTable<nif, staticSequence<nif>>(tableSize, *fd, *fe, blockSize);
  } else {
    std::cerr << "Error: modo hash no válido.\n";
    delete fd;
    return EXIT_FAILURE;
  }

  int option = -1;
  do {
    std::cout << "\n===== TABLA HASH =====\n";
    std::cout << "1. Insertar NIF\n";
    std::cout << "2. Buscar NIF\n";
    std::cout << "3. Mostrar tabla\n";
    std::cout << "0. Salir\n";
    std::cout << "Opcion: ";
    std::cin >> option;

    if (option == 1) {
      std::cout << "Introduce un NIF de 8 digitos (0 = aleatorio): ";
      long value;
      std::cin >> value;

      nif key = (value == 0) ? nif() : nif(value);

      if (table->insert(key)) {
        std::cout << "Insertado: " << key << "\n";
      } else {
        std::cout << "No se pudo insertar (duplicado o tabla llena).\n";
      }

    } else if (option == 2) {
      std::cout << "Introduce el NIF a buscar: ";
      long value;
      std::cin >> value;

      nif key(value);

      if (table->search(key)) {
        std::cout << "NIF encontrado.\n";
      } else {
        std::cout << "NIF no encontrado.\n";
      }

    } else if (option == 3) {
      std::cout << "\n--- Estado de la tabla ---\n";
      table->print(std::cout);
      std::cout << "--------------------------\n";
    }

  } while (option != 0);

  delete table;
  delete fe;
  delete fd;

  return EXIT_SUCCESS;
}