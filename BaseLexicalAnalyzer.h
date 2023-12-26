//
// Created by nikita on 26.12.23.
//

#ifndef LAB2_BASELEXICALANALYZER_H
#define LAB2_BASELEXICALANALYZER_H

#include <string>
#include <stdexcept>

struct bad_analyze : public virtual std::runtime_error {
  template<typename Arg>
  [[maybe_unused]] explicit bad_analyze(Arg&& arg) : std::runtime_error(std::forward<Arg>(arg)) {}
};

class BaseLexicalAnalyzer {
  static char constexpr END = 0;
public:
  explicit BaseLexicalAnalyzer(std::string inputLine) noexcept;

  bad_analyze error(std::string const& message) const noexcept;;
protected:
  char take() noexcept;
  bool test(char value) const noexcept;
  bool take(char value) noexcept;
  bool take(const char* line) noexcept;
  void expect(const char value);
  bool end() const noexcept;
  bool between(char a, char b) const noexcept;
private:
  bool hasNext() const noexcept;
  char next() noexcept;

  void mark() noexcept;
  void reset() noexcept;

  std::string const source;
  int pos{0};
  int savedPos{0};

  char current;
  char savedCurrent{0};
};

#endif // LAB2_BASELEXICALANALYZER_H
