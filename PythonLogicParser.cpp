//
// Created by nikita on 26.12.23.
//

#include "PythonLogicParser.h"
PythonLogicParser::PythonLogicParser(std::string line) noexcept : analyzer(std::move(line)) {
  analyzer.skipToken();
}

Tree::Ptr PythonLogicParser::parse() {
  auto result = parseE();
  switch (analyzer.currentToken()) {
  case Token::END:
    return result;
  default:
    throw analyzer.error("Unexpexted token after E");
  }
}

Tree::Ptr PythonLogicParser::parseE() {
  std::vector<Tree::Ptr> children;

  children.push_back(parseT());
  children.push_back(parseE_());

  switch (analyzer.currentToken()) {
  case Token::END:
  case Token::RPAREN:
    return std::make_unique<Tree>(id("E"), std::move(children));
  default:
    throw analyzer.error("Unexpexted token after E");
  }
}

Tree::Ptr PythonLogicParser::parseT() {
  std::vector<Tree::Ptr> children;

  children.emplace_back(parseM());
  children.emplace_back(parseT_());

  switch (analyzer.currentToken()) {
  case Token::END:
  case Token::RPAREN:
  case Token::XOR:
    return std::make_unique<Tree>(id("T"), std::move(children));
  default:
    throw analyzer.error("Unexpexted token after T");
  }
}

Tree::Ptr PythonLogicParser::parseM() {
  std::vector<Tree::Ptr> children;

  children.emplace_back(parseN());
  children.emplace_back(parseM_());

  switch (analyzer.currentToken()) {
  case Token::END:
  case Token::RPAREN:
  case Token::OR:
  case Token::XOR:
    return std::make_unique<Tree>(id("T"), std::move(children));
  default:
    throw analyzer.error("Unexpexted token after T");
  }
}

Tree::Ptr PythonLogicParser::parseN() {
  std::vector<Tree::Ptr> children;

  switch (analyzer.currentToken()) {
  case Token::NOT: {
    analyzer.skipToken();

    children.emplace_back(std::make_unique<Tree>(id("not")));
    children.emplace_back(parseN());

    switch (analyzer.currentToken()) {
    case Token::END:
    case Token::RPAREN:
    case Token::AND:
    case Token::XOR:
    case Token::OR:
      return std::make_unique<Tree>(id("N"), std::move(children));
    default:
      throw analyzer.error("Unexpexted token after N");
    }
  }
  case Token::LPAREN:
  case Token::VARIABLE: {

    children.emplace_back(parseI());

    switch (analyzer.currentToken()) {
    case Token::END:
    case Token::RPAREN:
    case Token::AND:
    case Token::XOR:
    case Token::OR:
      return std::make_unique<Tree>(id("N"), std::move(children));
    }
  }
  default:
    throw analyzer.error("Unexpexted token after N");
  }
}

Tree::Ptr PythonLogicParser::parseE_() {
  std::vector<Tree::Ptr> children;

  switch (analyzer.currentToken()) {
  case Token::XOR: {
    analyzer.skipToken();

    children.emplace_back(std::make_unique<Tree>(id("xor")));
    children.emplace_back(parseT());
    children.emplace_back(parseE_());

    switch (analyzer.currentToken()) {
    case Token::END:
    case Token::RPAREN:
      return std::make_unique<Tree>(id("E_"), std::move(children));
    default:
      throw analyzer.error("Unexpexted token after E_");
    }
  }
  default:
    return std::make_unique<Tree>(id("E_"));
  }
}

Tree::Ptr PythonLogicParser::parseT_() {
  std::vector<Tree::Ptr> children;

  switch (analyzer.currentToken()) {
  case Token::OR: {
    analyzer.skipToken();

    children.emplace_back(std::make_unique<Tree>(id("or")));
    children.emplace_back(parseM());
    children.emplace_back(parseT_());
    switch (analyzer.currentToken()) {
    case Token::END:
    case Token::RPAREN:
    case Token::XOR:
      return std::make_unique<Tree>(id("T_"), std::move(children));
    default:
      throw analyzer.error("Unexpexted token after T_");
    }
  }
  case Token::END:
  case Token::RPAREN:
  case Token::XOR:
    return std::make_unique<Tree>(id("T_"), std::move(children));
  default:
    throw analyzer.error("Unexpexted token after T_");
  }
}

Tree::Ptr PythonLogicParser::parseI() {
  std::vector<Tree::Ptr> children;

  switch (analyzer.currentToken()) {
  case Token::VARIABLE: {
    analyzer.skipToken();

    children.emplace_back(std::make_unique<Tree>(id("v")));

    children.emplace_back(parseI_());

    switch (analyzer.currentToken()) {
    case Token::END:
    case Token::RPAREN:
    case Token::AND:
    case Token::OR:
    case Token::XOR:
      return std::make_unique<Tree>(id("I"), std::move(children));
    default:
      throw analyzer.error("Unexpexted token after I_");
    }
  }
  case Token::LPAREN: {
    analyzer.skipToken();

    children.emplace_back(std::make_unique<Tree>("("));
    children.emplace_back(parseE());

    if (analyzer.currentToken() != Token::RPAREN) {
      throw analyzer.error("Expected closing ')'");
    }
    analyzer.skipToken();
    children.emplace_back(std::make_unique<Tree>(")"));

    switch (analyzer.currentToken()) {
    case Token::END:
    case Token::RPAREN:
    case Token::AND:
    case Token::OR:
    case Token::XOR:
      return std::make_unique<Tree>(id("I"), std::move(children));
    default:
      throw analyzer.error("Unexpexted token after I");
    }
  }
  default:
    throw analyzer.error("Unexpexted token after I'");
  }
}

Tree::Ptr PythonLogicParser::parseI_() {
  std::vector<Tree::Ptr> children;

  switch (analyzer.currentToken()) {
  case Token::IN: {
    analyzer.skipToken();

    children.emplace_back(std::make_unique<Tree>(id("in")));

    if (analyzer.currentToken() != Token::VARIABLE) {
      throw analyzer.error("Exprected variable");
    }
    analyzer.skipToken();
    children.emplace_back(std::make_unique<Tree>("v"));

    return std::make_unique<Tree>(id("I_"), std::move(children));
  }
  case Token::NOT_IN: {
    analyzer.skipToken();

    children.emplace_back(std::make_unique<Tree>(id("not_in")));

    if (analyzer.currentToken() != Token::VARIABLE) {
      throw analyzer.error("Exprected variable");
    }
    analyzer.skipToken();
    children.emplace_back(std::make_unique<Tree>("v"));

    return std::make_unique<Tree>(id("I_"), std::move(children));
  }
  default:
    return std::make_unique<Tree>(id("I_"));
  }
}

std::string PythonLogicParser::id(std::string name) {
  return name + std::to_string(index++);
}
Tree::Ptr PythonLogicParser::parseM_() {
  std::vector<Tree::Ptr> children;

  switch (analyzer.currentToken()) {
  case Token::AND: {
    analyzer.skipToken();

    children.emplace_back(std::make_unique<Tree>(id("and")));
    children.emplace_back(parseN());
    children.emplace_back(parseM_());

    switch (analyzer.currentToken()) {
    case Token::END:
    case Token::RPAREN:
    case Token::XOR:
    case Token::OR:
      return std::make_unique<Tree>(id("M_"), std::move(children));
    default:
      throw analyzer.error("Unexpexted token after M_");
    }
  }
  case Token::END:
  case Token::RPAREN:
  case Token::XOR:
  case Token::OR:
    return std::make_unique<Tree>(id("M_"));
  default:
    throw analyzer.error("Unexpexted token after M_");
  }
}
