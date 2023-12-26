#include <iostream>
#include "first_follow.h"
#include "PythonLogicParser.h"

void test1() {
  auto result = PythonLogicParser("not a").parse();
}

void test2() {
  auto result = PythonLogicParser("b not in a").parse();
}

void test3() {
  auto result = PythonLogicParser("a and bnot in a").parse();
}

void test4() {
  auto result = PythonLogicParser("a and bnot in a").parse();
}

bool good_tests() {
  void (*gtest[5])() = {
      &test1,
      &test2,
      &test3,
      &test4,
      &test5
  };
  size_t const size = sizeof(gtest) / sizeof(gtest[0]);
  int count = 0;

  for (int i = 0; i < size; ++i) {
    try {
      (gtest[i])();
      ++count;
      std::cout << "Success pass test" << i << '\n';
    } catch(...) {
      std::cout << "test" << i << " mustn't fail\n";
    }
  }
}

bool fail_test() {
  void (*ftest[5])() = {
      &test6,
      &test7,
      &test8,
      &test9,
      &test10
  };
  size_t const size = sizeof(ftest) / sizeof(ftest[0]);
  int count = 0;

  for (int i = 0; i < size; ++i) {
    try {
      (ftest[i])();
      ++count;
      std::cout << "test" << i << " must fail\n";
    } catch(...) {
      std::cout << "Success fail test" << i << '\n';
    }
  }

  return count == size;
}

int main() {

}
