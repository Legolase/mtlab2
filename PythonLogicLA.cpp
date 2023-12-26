//
// Created by nikita on 26.12.23.
//

#include "PythonLogicLA.h"
PythonLogicLA::PythonLogicLA(std::string inputLine) noexcept : BaseLexicalAnalyzer(std::move(inputLine)) {}

Token PythonLogicLA::nextToken() {
  static const std::map<std::string, Token> translator = {{")", Token::RPAREN}, {"(", Token::LPAREN}, {"in", Token::IN},
                                                          {"xor", Token::XOR},  {"or", Token::OR},    {"xor", Token::XOR},
                                                          {"and", Token::AND}};

  skipWhitespaces();

  // Analyze $ (end)
  if (end()) {
    return Token::END;
  }

  //  Analyze 'not in' and 'not'
  if (take("not")) {
    skipWhitespaces();
    if (take("in")) {
      return Token::NOT_IN;
    }
    return Token::NOT;
  }

  //  Analyze other simple keywords
  for (auto const& elem : translator) {
    if (take(elem.first.c_str())) {
      return elem.second;
    }
  }

  // Analyze variables
  if (between('a', 'z') || between('A', 'Z')) {
    take();
    return Token::VARIABLE;
  }

  throw error("Unknown element");
}

void PythonLogicLA::skipWhitespaces() {
  while (take(' ') || take('\t') || take('\r')) {
  }
}

void PythonLogicLA::skipToken() {
  currentToken_ = nextToken();
}

Token PythonLogicLA::currentToken() const noexcept {
  return currentToken_;
}
