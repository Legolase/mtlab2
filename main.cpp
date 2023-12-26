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
  auto result = PythonLogicParser("a and b not in a").parse();
}

void test4() {
  auto result = PythonLogicParser("a and bnot in a").parse();
}

void test5() {
  auto result = PythonLogicParser("a and (b or s)").parse();
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
      std::cout << "Success pass test" << i + 1 << '\n';
    } catch(std::exception& e) {
      std::cout << "test" << i + 1 << " mustn't fail -> " << e.what() << '\n';
    } catch(...) {
      std::cout << "test" << i + 1 << " mustn't fail\n";
    }
  }

  return count == size;
}

void test6() {
  auto result = PythonLogicParser("not 4").parse();
}

void test7() {
  auto result = PythonLogicParser("b not in in a").parse();
}

void test8() {
  auto result = PythonLogicParser("(a and b) not in a").parse();
}

void test9() {
  auto result = PythonLogicParser("abb and bnot in a").parse();
}

void test10() {
  auto result = PythonLogicParser("s)").parse();
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
      std::cout << "test" << i + 6 << " must fail\n";
    } catch(...) {
      std::cout << "Success fail test" << i + 6 << '\n';
    }
  }

  return count == size;
}

int main() {
  good_tests();
  fail_test();
}
