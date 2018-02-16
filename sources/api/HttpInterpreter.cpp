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

  struct HttpResponse   HttpInterpreter::get(struct HttpRequest const &request) {
    struct HttpResponse response;

    response = getDefaultResponse();
    if (request.uri.substr(request.uri.size() - 5, 5).compare(".html") == 0) {
      //Utils::getFile(_root + request.uri);
      std::cout << ".html found" << '\n';
    }
    return response;
  }
} /* zia:api */
