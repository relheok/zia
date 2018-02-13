#ifndef HTTPPARSER_HPP_
# define HTTPPARSER_HPP_

#include <string>
#include "http.h"
#include "Utils.hpp"
#include "Error.hpp"

namespace zia::api {
  class                 HttpParser {
  public:
    HttpParser();
    ~HttpParser();

    /**
    * Parse the string [input] to make a HttpRequest
    * Exception : BadRequestError, InvalidMethodError
    * \return the request
    */
    struct HttpRequest  parseRequest(std::string const &input);

  private:
    struct HttpRequest  parsePostRequest(std::vector<std::string> const &);
    struct HttpRequest  parseGetRequest(std::vector<std::string> const &);

    std::map<std::string, std::string>  getHeaders(std::vector<std::string> const &);

  };
} /* zia::api */

#endif /* end of include guard: HTTPPARSER_HPP_ */
