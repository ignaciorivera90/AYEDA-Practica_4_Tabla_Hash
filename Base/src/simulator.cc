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
// Archivo simulator.cc: implementación de la clase Simulator encargada de
//                       procesar argumentos, construir la tabla hash y
//                       ejecutar el menú interactivo.

#include "simulator.h"

#include <cstdlib>
#include <iostream>
#include <limits>

/**
 * @brief Builds the simulator from command line arguments.
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 */
Simulator::Simulator(int argc, char* argv[])
    : table_size_(0),
      block_size_(0),
      fd_code_(0),
      fe_code_(0),
      hash_type_(""),
      fd_(nullptr),
      fe_(nullptr),
      hash_table_(nullptr) {
  ParseArguments(argc, argv);
  BuildHashTable();
}

/**
 * @brief Frees dynamic memory used by the simulator.
 */
Simulator::~Simulator() {
  delete hash_table_;
  delete fe_;
  delete fd_;
}

/**
 * @brief Parses and validates command line arguments.
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @throws InvalidArgumentException if an argument is invalid.
 * @throws MissingArgumentException if required parameters are missing.
 */
void Simulator::ParseArguments(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-ts") {
      if (i + 1 >= argc) {
        throw MissingArgumentException("falta valor para -ts");
      }
      table_size_ = std::stoul(argv[++i]);
    } else if (arg == "-fd") {
      if (i + 1 >= argc) {
        throw MissingArgumentException("falta valor para -fd");
      }
      std::string value = argv[++i];

      if (value == "module") fd_code_ = 1;
      else if (value == "sum") fd_code_ = 2;
      else if (value == "pseudorandom") fd_code_ = 3;
      else throw InvalidArgumentException("fd invalido");
    } else if (arg == "-hash") {
      if (i + 1 >= argc) {
        throw MissingArgumentException("falta valor para -hash");
      }
      hash_type_ = argv[++i];
    } else if (arg == "-bs") {
      if (i + 1 >= argc) {
        throw MissingArgumentException("falta valor para -bs");
      }
      block_size_ = std::stoul(argv[++i]);
    } else if (arg == "-fe") {
      if (i + 1 >= argc) {
        throw MissingArgumentException("falta valor para -fe");
      }
      fe_code_ = std::stoi(argv[++i]);
    } else {
      throw InvalidArgumentException("argumento desconocido: " + arg);
    }
  }

  if (table_size_ == 0) {
    throw InvalidArgumentException("el tamaño de tabla debe ser > 0");
  }

  if (fd_code_ < 1 || fd_code_ > 3) {
    throw InvalidArgumentException("la función de dispersión debe ser 1, 2 o 3");
  }

  if (hash_type_ != "open" && hash_type_ != "close") {
    throw InvalidArgumentException("el modo hash debe ser 'open' o 'close'");
  }

  if (hash_type_ == "close") {
    if (block_size_ == 0) {
      throw MissingArgumentException("en dispersión cerrada debes indicar -bs <n>");
    }
    if (fe_code_ < 1 || fe_code_ > 4) {
      throw MissingArgumentException("en dispersión cerrada debes indicar -fe <1..4>");
    }
  }
}

/**
 * @brief Creates the configured hash table and its associated functions.
 * @throws InvalidArgumentException if any configuration code is invalid.
 */
void Simulator::BuildHashTable() {
  switch (fd_code_) {
    case 1:
      fd_ = new ModuleDispersion<nif>(table_size_);
      break;
    case 2:
      fd_ = new SumDispersion<nif>(table_size_);
      break;
    case 3:
      fd_ = new PseudoRandomDispersion<nif>(table_size_);
      break;
    default:
      throw InvalidArgumentException("codigo de dispersión no válido");
  }

  if (hash_type_ == "open") {
    hash_table_ = new HashTable<nif, dynamicSequence<nif>>(table_size_, *fd_);
    return;
  }

  switch (fe_code_) {
    case 1:
      fe_ = new LinearExploration<nif>();
      break;
    case 2:
      fe_ = new QuadraticExploration<nif>();
      break;
    case 3:
      fe_ = new DoubleDispersionExploration<nif>(*fd_);
      break;
    case 4:
      fe_ = new RedispersionExploration<nif>(table_size_);
      break;
    default:
      throw InvalidArgumentException("codigo de exploración no válido");
  }

  hash_table_ =
      new HashTable<nif, staticSequence<nif>>(table_size_, *fd_, *fe_, block_size_);
}

/**
 * @brief Clears the console screen.
 */
void Simulator::ClearScreen() const {
#ifdef _WIN32
  std::system("cls");
#else
  std::system("clear");
#endif
}

/**
 * @brief Pauses execution until ENTER is pressed.
 */
void Simulator::Pause() const {
  std::cout << "\nPulse ENTER para continuar...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
}

/**
 * @brief Prints the simulator header.
 */
void Simulator::PrintHeader() const {
  std::cout << "=====================================\n";
  std::cout << "     PRACTICA 4 - TABLA HASH\n";
  std::cout << "=====================================\n";
  std::cout << "Tamano tabla: " << table_size_ << '\n';
  std::cout << "Modo: " << hash_type_ << '\n';
  if (hash_type_ == "close") {
    std::cout << "Tamano bloque: " << block_size_ << '\n';
  }
  std::cout << "=====================================\n\n";
}

/**
 * @brief Shows the available menu options.
 */
void Simulator::ShowMenu() const {
  std::cout << "1. Insertar NIF\n";
  std::cout << "2. Buscar NIF\n";
  std::cout << "3. Mostrar tabla\n";
  std::cout << "0. Salir\n";
  std::cout << "\nOpcion: ";
}

/**
 * @brief Handles insertion of a key entered by the user.
 *
 * @details
 * If the input is not numeric or does not have 8 digits,
 * an error message is shown and control returns to the menu.
 */
void Simulator::HandleInsert() {
  long value;
  std::cout << "Introduce un NIF de 8 digitos (0 = aleatorio): ";
  std::cin >> value;

  if (!std::cin) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nError: entrada no numerica.\n";
    Pause();
    return;
  }

  if (value != 0 && (value < 10000000 || value > 99999999)) {
    std::cout << "\nError: el NIF debe tener 8 digitos.\n";
    Pause();
    return;
  }

  nif key = (value == 0) ? nif() : nif(value);

  if (hash_table_->insert(key)) {
    std::cout << "\nNIF insertado correctamente: " << key << '\n';
  } else {
    std::cout << "\nNo se pudo insertar el NIF (duplicado o tabla llena).\n";
  }

  Pause();
}

/**
 * @brief Handles search of a key entered by the user.
 *
 * @details
 * If the input is not numeric or does not have 8 digits,
 * an error message is shown and control returns to the menu.
 */
void Simulator::HandleSearch() {
  long value;
  std::cout << "Introduce el NIF a buscar: ";
  std::cin >> value;

  if (!std::cin) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nError: entrada no numerica.\n";
    Pause();
    return;
  }

  if (value < 10000000 || value > 99999999) {
    std::cout << "\nError: el NIF debe tener 8 digitos.\n";
    Pause();
    return;
  }

  nif key(value);

  if (hash_table_->search(key)) {
    std::cout << "\nNIF encontrado.\n";
  } else {
    std::cout << "\nNIF no encontrado.\n";
  }

  Pause();
}

/**
 * @brief Prints the current state of the hash table.
 */
void Simulator::HandlePrint() const {
  std::cout << "--- Estado actual de la tabla ---\n";
  hash_table_->print(std::cout);
}

/**
 * @brief Runs the interactive simulator menu.
 *
 * @details
 * Repeatedly shows the menu, reads the selected option
 * and executes the requested operation until the user exits.
 */
void Simulator::Run() {
  int option = -1;

  while (option != 0) {
    ClearScreen();
    PrintHeader();
    ShowMenu();

    std::cin >> option;

    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "\nError: la opcion del menu debe ser numerica.\n";
      Pause();
      continue;
    }

    ClearScreen();
    PrintHeader();

    switch (option) {
      case 1:
        HandleInsert();
        break;
      case 2:
        HandleSearch();
        break;
      case 3:
        HandlePrint();
        Pause();
        break;
      case 0:
        std::cout << "Saliendo del programa...\n";
        break;
      default:
        std::cout << "Error: opcion de menu no valida.\n";
        Pause();
        break;
    }
  }
}