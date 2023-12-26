//
// Created by nikita on 26.12.23.
//

#ifndef LAB2_PYTHONLOGICPARSER_H
#define LAB2_PYTHONLOGICPARSER_H

#include "PythonLogicLA.h"
#include "Tree.h"

struct PythonLogicParser {
  explicit PythonLogicParser(std::string line) noexcept;

  Tree::Ptr parse();

private:
  PythonLogicLA analyzer;
  int index{0};

  std::string id(std::string name);

  Tree::Ptr parseE();
  Tree::Ptr parseT();
  Tree::Ptr parseE_();
  Tree::Ptr parseN();
  Tree::Ptr parseT_();
  Tree::Ptr parseI();
  Tree::Ptr parseI_suff();
  Tree::Ptr parseA();
  Tree::Ptr parseI_();
};

#endif // LAB2_PYTHONLOGICPARSER_H
