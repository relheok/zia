#include "Utils.hpp"

std::vector<std::string>    Utils::split(std::string const &str, std::string const &delimiters) {
  std::vector<std::string>  v;
  char                      *tmp;
  char                      *toFree = strdup(str.c_str());

  tmp = strtok(toFree, delimiters.c_str());
  while (tmp != NULL) {
    v.push_back(tmp);
    tmp = strtok(NULL, delimiters.c_str());
  }
  free(toFree);
  return v;
}

std::string   Utils::trim(std::string const &str) {
  size_t      first = str.find_first_not_of(' ');
  size_t      last = str.find_last_not_of(' ');

  if (first == std::string::npos)
    return str;
  return str.substr(first, (last - first + 1));
}

std::string   Utils::readFile(std::string const &path) {
  if (access(path.c_str(), F_OK | R_OK) == -1)
    throw FileNotFound(path);
  std::ifstream file(path);
	std::string str((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
  return str;
}
