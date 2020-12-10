#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace utils {
  inline std::string trim(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
      it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
      rit++;

    return std::string(it, rit.base());
  }

  inline std::vector<std::string> split(const std::string& str, const std::string& delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
      pos = str.find(delim, prev);
      if (pos == std::string::npos) pos = str.length();
      std::string token = str.substr(prev, pos - prev);
      if (!token.empty()) tokens.push_back(token);
      prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
  }

  inline int findIndex(std::vector<int> vector, int element) {
    int size = vector.size();
    for(int i = 0; i < size; i++) {
      if(vector[i] == element) {
        return i;
      }
    }
    return -1;
  }
}