#ifndef FIRST_FOLLOW_H
#define FIRST_FOLLOW_H

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>

template<typename T>
using v = std::vector<T>;

template<typename T>
using s = std::set<T>;

template<typename A, typename B>
using pr = std::pair<A, B>;

template<typename A, typename B>
using m = std::map<A, B>;

using str = std::string;

m<str, v<v<str>>> get_rules(str& first_neterm);

m<str, s<str>> first(m<str, v<v<str>>> const& rules);

m<str, s<str>> follow(m<str, v<v<str>>> const& rules, m<str, s<str>> const& first_array, str const& first_neterm);

void get_first_follow();

#endif