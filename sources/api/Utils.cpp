#include "Utils.hpp"

std::vector<std::string>    Utils::split(std::string const &str, std::string const &delimiters) {
  std::vector<std::string>  v;
  char                      *tmp = strdup(str.c_str());

  tmp = strtok(tmp, delimiters.c_str());
  while (tmp != NULL) {
    v.push_back(tmp);
    tmp = strtok(NULL, delimiters.c_str());
  }
  return v;
}

std::string   Utils::trim(std::string const &str) {
  size_t      first = str.find_first_not_of(' ');
  size_t      last = str.find_last_not_of(' ');

  if (first == std::string::npos)
    return str;
  return str.substr(first, (last - first + 1));
}
