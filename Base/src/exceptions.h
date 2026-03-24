#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <stdexcept>
#include <string>

class Exception : public std::runtime_error {
 public:
  explicit Exception(const std::string& message)
      : std::runtime_error(message) {}
};

class MissingArgumentException : public Exception {
 public:
  explicit MissingArgumentException(const std::string& message)
      : Exception("MissingArgumentException: " + message) {}
};

class InvalidArgumentException : public Exception {
 public:
  explicit InvalidArgumentException(const std::string& message)
      : Exception("InvalidArgumentException: " + message) {}
};

class InvalidOptionException : public Exception {
 public:
  explicit InvalidOptionException(const std::string& message)
      : Exception("InvalidOptionException: " + message) {}
};

#endif