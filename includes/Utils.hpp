#ifndef UTILS_HPP_
# define UTILS_HPP_

#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>
#include "Error.hpp"

class Utils {
public:
  /**
  * Split the string [str] at [delimiters]
  * \return a vector of the splited string
  */
  static std::vector<std::string> split(std::string const &str, std::string const &delimiters);

  /**
  * Remove spaces and tabs at the begin and at the end of the string [str]
  * \return the new string
  */
  static std::string  trim(std::string const &str);

  /**
  * Open and read the file [path]
  * throws FileNotFound
  * \return the opened file
  */
  static std::string  readFile(std::string const &path);
};

#endif /* end of include guard: UTILS_HPP_ */
