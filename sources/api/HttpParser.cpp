#include "HttpParser.hpp"

namespace zia::api {
  HttpParser::HttpParser() {}

  HttpParser::~HttpParser() {}

  struct HttpRequest          HttpParser::parse(std::string const &str) const {
    std::vector<std::string>  v;
    std::vector<std::string>  line;
    struct HttpRequest        request;

    v = Utils::split(str, "\n");
    line = Utils::split(inspectHttpLine(v[0]), " ");
    if (line.size() != 3)
      throw BadRequestError("invalid command line");
    request.version = getVersion(line[2]);
    request.headers = getHeaders(v);
    request.body = getBody(v);
    request.method = getMethod(line[0]);
    request.uri = line[1];
    return request;
  }

  void        HttpParser::test(struct HttpRequest &request) const {
    std::cout << "HttpParser Test Function" << '\n';
    std::cout << "Http Version : " << (int)request.version << '\n';
    std::cout << "Headers :" << '\n';
    for (std::map<std::string, std::string>::iterator it = request.headers.begin() ; it != request.headers.end(); it++)
      std::cout << it->first << " -> " << it->second << '\n';
    std::cout << "Body :" << '\n';
    for (Net::Raw::iterator it = request.body.begin(); it != request.body.end(); it++)
      std::cout << (char)*it;
    std::cout << std::endl;
    std::cout << "Http Method : " << (int)request.method << '\n';
    std::cout << "URI : " << request.uri << '\n';
  }

  http::Version   HttpParser::getVersion(std::string const &version) const {
    if (version.compare("HTTP/0.9") == 0)
      return http::Version::http_0_9;
    if (version.compare("HTTP/1.0") == 0)
      return http::Version::http_1_0;
    if (version.compare("HTTP/1.1") == 0)
      return http::Version::http_1_1;
    if (version.compare("HTTP/2.0") == 0)
      return http::Version::http_2_0;
    return http::Version::unknown;
  }

  std::map<std::string, std::string>    HttpParser::getHeaders(std::vector<std::string> const &v) const {
    std::map<std::string, std::string>  m;
    std::vector<std::string>            line;
    unsigned int                        i = 1;

    while (i < v.size() && v[i].compare("\r") != 0) {
      line = Utils::split(inspectHttpLine(v[i]), ":");
      if (line.size() != 2)
        throw BadRequestError("invalid header (no key)");
      if (line[1][0] != ' ')
        throw BadRequestError("invalid header (no space)");
      m[line[0]] = line[1].substr(1);
      i++;
    }
    return m;
  }

  Net::Raw        HttpParser::getBody(std::vector<std::string> const &v) const {
    Net::Raw      body;
    unsigned int  i = 1;
    std::string   sbody = "";

    while (i < v.size() && v[i].compare("\r") != 0)
      i++;
    i++;
    if (i >= v.size())
      return body;
    while (i < v.size()) {
      sbody += v[i];
      i++;
      if (i < v.size())
        sbody += '\n';
    }
    sbody = sbody.substr(0, sbody.size() - 1);
    for (size_t j = 0; j < sbody.size(); j++)
      body.push_back(std::byte(sbody[j]));
    return body;
  }

  http::Method  HttpParser::getMethod(std::string const &method) const {
    if (method.compare("POST") == 0)
      return http::Method::post;
    else if (method.compare("GET") == 0)
      return http::Method::get;
    return http::Method::unknown;
  }

  std::string   HttpParser::inspectHttpLine(std::string const &str) const {
    std::string nstr;

    if (Utils::trim(str) != str || str.size() < 1)
      throw BadRequestError("invalid http line");
    return str.substr(0, str.size() - 1);
  }

} /* zia::api */
