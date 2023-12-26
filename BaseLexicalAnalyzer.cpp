//
// Created by nikita on 26.12.23.
//

#include "BaseLexicalAnalyzer.h"
#include <sstream>

BaseLexicalAnalyzer::BaseLexicalAnalyzer(std::string inputLine) noexcept : source(std::move(inputLine)) {
  take();
  mark();
}

bool BaseLexicalAnalyzer::hasNext() const noexcept {
  return pos < source.size();
}

char BaseLexicalAnalyzer::take() noexcept {
  const char result = current;
  current = next();
  return result;
}

char BaseLexicalAnalyzer::next() noexcept {
  return hasNext() ? source[pos++] : END;
}

bool BaseLexicalAnalyzer::test(const char value) const noexcept {
  return value == current;
}

bool BaseLexicalAnalyzer::take(char value) noexcept {
  if (test(value)) {
    take();
    return true;
  }
  return false;
}

bool BaseLexicalAnalyzer::take(const char* line) noexcept {
  if (!line[0]) {
    return true;
  }

  mark();
  int linePos = 0;

  while (true) {
    if (!line[linePos]) {
      break;
    }
    if (!take(line[linePos++])) {
      reset();
      return false;
    }
  }

  return true;
}

void BaseLexicalAnalyzer::expect(const char value) {
  if (!take(value)) {
    std::stringstream stream;
    stream << "Unexpected symbol code(" << static_cast<int>(current) << ")";
    throw bad_analyze(stream.str());
  }
}

bad_analyze BaseLexicalAnalyzer::error(std::string const& message) const noexcept {
  std::stringstream stream;
  stream << "Exception at " << pos << ": " << message;
  return bad_analyze(stream.str());
}

bool BaseLexicalAnalyzer::end() const noexcept {
  return test(END);
}

bool BaseLexicalAnalyzer::between(char a, char b) const noexcept {
  return (current >= std::min(a, b)) && (current <= std::max(a, b));
}

void BaseLexicalAnalyzer::mark() noexcept {
  savedPos = pos;
  savedCurrent = current;
}

void BaseLexicalAnalyzer::reset() noexcept {
  pos = savedPos;
  current = savedCurrent;
}
