#include "HttpInterpreter.hpp"

namespace zia::api {
  HttpInterpreter::HttpInterpreter(std::string const &root) : _root(root) {}

  HttpInterpreter::HttpInterpreter(HttpInterpreter const &original) {
    _root = original.getRoot();
  }

  HttpInterpreter   &HttpInterpreter::operator=(HttpInterpreter const &original) {
    _root = original._root;
    return *this;
  }

  HttpInterpreter::~HttpInterpreter() {}

  struct HttpResponse   HttpInterpreter::interpret(struct HttpRequest const &request) {
    switch (request.method) {
      case http::Method::get:
        return get(request);
        break;
      case http::Method::head:
        return get(request, false);
      default:
        return getDefaultResponse(http::common_status::method_not_allowed, "Method not allowed");
        break;
    }
  }

  struct HttpResponse   HttpInterpreter::getDefaultResponse(http::Status const &status, std::string const &reason) {
    struct HttpResponse response;
    time_t              t = std::time(nullptr);

    response.version = http::Version::http_1_1;
    response.status = status;
    response.reason = reason;
    char buf[42];
    std::strftime(buf, 42, "%a, %d %b %Y %H:%M:%S GMT", std::gmtime(&t));
    response.headers["Date"] = buf;
    response.headers["Server"] = SERVER_NAME + std::string("/") + SERVER_VERSION;
    return response;
  }

  struct HttpResponse         HttpInterpreter::get(struct HttpRequest const &request, bool body) {
    struct HttpResponse       response;
    std::vector<std::string>  v = Utils::split(request.uri, "?");

    try {
      response = getDefaultResponse(http::common_status::ok, "OK");
      if (v[0].size() >= 5 && (v[0].substr(v[0].size() - 5, 5).compare(".html") == 0 || v[0].substr(v[0].size() - 4, 4).compare(".htm") == 0)) {
        response.body = getBody(Utils::readFile(_root + request.uri));
        response.headers["Content-Type"] = "text/html; charset=UTF-8";
        response.headers["Content-Length"] = std::to_string(response.body.size());
        if (!body)
          response.body.clear();
      }
    } catch (FileNotFound) {
      return getDefaultResponse(http::common_status::not_found, "Not found");
    }
    return response;
  }

  Net::Raw    HttpInterpreter::getBody(std::string const &str) {
    Net::Raw  body;

    for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
      body.push_back(std::byte(*it));
    return body;
  }
} /* zia:api */
