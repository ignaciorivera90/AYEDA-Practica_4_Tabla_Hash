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