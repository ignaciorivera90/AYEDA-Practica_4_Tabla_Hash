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
// Archivo funciones.h: declaración de la función Usage para validar los
//                     argumentos de entrada del programa.

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

/**
 * @brief Shows help if '--help' is provided and validates arguments.
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @throws MissingArgumentException if mandatory arguments are missing.
 */
void Usage(int argc, char* argv[]);

#endif