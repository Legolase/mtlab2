#include "first_follow.h"

m<str, v<v<str>>> get_rules(str& first_neterm) {
  std::stringstream stream;
  str pref;
  str suff;
  int n;
  std::cin >> n;

  m<str, v<v<str>>> result;

  for (int i = 0; i < n; ++i) {
    stream.clear();
    std::cin >> pref;

    if (i == 0) {
      first_neterm = pref;
    }

    if (result.find(pref) == result.end()) {
      result[pref] = v<v<str>>{};
    }
    result[pref].emplace_back();

    std::getline(std::cin, suff);
    stream << suff;

    while (stream >> suff) {
      result[pref].back().push_back(std::move(suff));
    }
  }

  return result;
}

static bool is_terminal(str const& elem) {
  return (elem[0] < 65) || (elem[0] > 90);
}

static void first_impl(m<str, v<v<str>>> const& rules, m<str, s<str>> const& result, v<str> const& alpha, int const index,
                       s<str>& to) {
  if (index >= alpha.size()) {
    to.insert("_");
    return;
  }

  if (is_terminal(alpha[index])) {
    to.insert(alpha[index]);
  }
  else if (alpha[index] == "_") {
    to.insert("_");
  }
  else {
    auto const& it = result.find(alpha[index]);

    if (it == result.end()) {
      return;
    }
    auto const& firstA = result.at(alpha[index]);

    for (auto const& elem : firstA) {
      if (elem != "_") {
        to.insert(elem);
      }
    }

    if (firstA.find("_") != firstA.end()) {
      first_impl(rules, result, alpha, index + 1, to);
    }
  }
}

m<str, s<str>> first(m<str, v<v<str>>> const& rules) {
  m<str, s<str>> result;
  bool change = true;
  int prev_size;

  while (change) {
    change = false;

    for (auto const& neterm : rules) {
      if (result.find(neterm.first) == result.end()) {
        result[neterm.first] = s<str>{};
      }
      prev_size = result[neterm.first].size();

      for (auto const& alpha : neterm.second) {
        first_impl(rules, result, alpha, 0, result[neterm.first]);
      }

      if (result[neterm.first].size() != prev_size) {
        change = true;
      }
    }
  }

  return result;
}

static void add_after_A(m<str, s<str>> const& result, v<str> const& alpha, int const index, str const& A, s<str>& to) {
  auto const& itA = result.find(A);

  if (itA == result.end()) {
    return;
  }

  auto const& gammaA = result.at(A);

  for (auto const& elem : gammaA) {
    to.insert(elem);
  }
}

static void follow_impl(m<str, v<v<str>>> const& rules, m<str, s<str>> const& first_array, m<str, s<str>> const& result,
                 v<str> const& alpha, int const index, str const& A, s<str>& to) {
  if (index >= alpha.size()) {
    throw std::runtime_error("Fuck2");
  }

  if (index + 1 == alpha.size()) {
    add_after_A(result, alpha, index, A, to);
    return;
  }

  if (is_terminal(alpha[index + 1])) {
    to.insert(str(1, alpha[index + 1][0]));
  }
  else {
    auto const& it = first_array.find(alpha[index + 1]);

    if (it == first_array.end()) {
      return;
    }

    auto const& gamma = first_array.at(alpha[index + 1]);

    for (auto const& elem : gamma) {
      if (elem != "_") {
        to.insert(elem);
      }
    }

    if (gamma.find("_") != gamma.end()) {
      add_after_A(result, alpha, index, A, to);
    }
  }
}

m<str, s<str>> follow(m<str, v<v<str>>> const& rules, m<str, s<str>> const& first_array, str const& first_neterm) {
  m<str, s<str>> result;
  bool change = true;
  int prev_size, i;

  result[first_neterm] = { "$" };

  while (change) {
    change = false;

    for (auto const& neterm : rules) {
      if (result.find(neterm.first) == result.end()) {
        result[neterm.first] = s<str>{};
      }

      for (auto const& alpha : neterm.second) {
        for (i = 0; i < alpha.size(); ++i) {
          if (!is_terminal(alpha[i])) {
            prev_size = result[alpha[i]].size();

            follow_impl(rules, first_array, result, alpha, i, neterm.first, result[alpha[i]]);

            if (result[alpha[i]].size() != prev_size) {
              change = true;
            }
          }
        }
      }
    }
  }

  return result;
}

void get_first_follow() {
  str first_neterm;
  auto rules = get_rules(first_neterm);

  auto first_arr = first(rules);

  std::cout << "================\n";

  for (auto const& elem : first_arr) {
    std::cout << elem.first << " -> ";

    for (auto const& symbol : elem.second) {
      std::cout << symbol << ' ';
    }
    std::cout << '\n';
  }

  auto follow_arr = follow(rules, first_arr, first_neterm);

  std::cout << "================\n";

  for (auto const& elem : follow_arr) {
    std::cout << elem.first << " -> ";

    for (auto const& symbol : elem.second) {
      std::cout << symbol << ' ';
    }
    std::cout << '\n';
  }
}
