//
// Created by nikita on 26.12.23.
//

#ifndef LAB2_PYTHONLOGICLA_H
#define LAB2_PYTHONLOGICLA_H

#include "BaseLexicalAnalyzer.h"
#include <map>

enum class Token {
  OR,
  AND,
  NOT,
  NOT_IN,
  IN,
  XOR,
  LPAREN,
  RPAREN,
  VARIABLE,
  END
};

struct PythonLogicLA : public BaseLexicalAnalyzer {
  explicit PythonLogicLA(std::string inputLine) noexcept;

  void skipToken();
  Token currentToken() const noexcept;
private:
  void skipWhitespaces();
  Token nextToken();

  Token currentToken_{0};
};

#endif // LAB2_PYTHONLOGICLA_H
