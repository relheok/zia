#include "HttpParser.hpp"

namespace zia::api {
  HttpParser::HttpParser() {}

  HttpParser::~HttpParser() {}

  struct HttpRequest          HttpParser::parseRequest(std::string const &str) {
    std::vector<std::string>  v;
    std::vector<std::string>  line;

    v = Utils::split(Utils::trim(str), "\n");
    line = Utils::split(Utils::trim(v[0]), " ");
    if (line.size() != 3)
      throw BadRequestError();

    if (line[0].compare("POST") == 0)
      return parsePostRequest(v);
    else if (line[0].compare("GET") == 0)
      return parseGetRequest(v);

    throw InvalidMethodError();
  }

  struct HttpRequest          HttpParser::parsePostRequest(std::vector<std::string> const &v) {
    struct HttpRequest        request;
    std::vector<std::string>  line;

    (void)v;
    request.method = http::Method::post;
    return request;
  }

  struct HttpRequest          HttpParser::parseGetRequest(std::vector<std::string> const &v) {
    struct HttpRequest        request;
    std::vector<std::string>  line;

    request.method = http::Method::get;
    return request;
  }

  std::map<std::string, std::string>    HttpParser::getHeaders(std::vector<std::string> const &v) {
    std::map<std::string, std::string>  m;
    int i = 1;

    while (i < v.size() && v[0].compare("") != 0) {
      
    }
    return m;
  }
} /* zia::api */
