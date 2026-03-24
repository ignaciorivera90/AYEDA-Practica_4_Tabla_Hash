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