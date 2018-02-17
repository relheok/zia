#include "HttpInterpreter.hpp"

namespace zia::api {
  HttpInterpreter::HttpInterpreter(std::string const &root) : _root(root) {}

  HttpInterpreter::HttpInterpreter(HttpInterpreter const &original) {
    _root = original._root;
    _parser = original._parser;
  }

  HttpInterpreter   &HttpInterpreter::operator=(HttpInterpreter const &original) {
    _root = original._root;
    _parser = original._parser;
    return *this;
  }

  HttpInterpreter::~HttpInterpreter() {}

  std::string           HttpInterpreter::interpret(std::string const &request) {
    struct HttpResponse response;
    struct HttpRequest r;

    try {
      r = _parser.parse(request);
      switch (r.method) {
        case http::Method::get:
          response = get(r);
          break;
        case http::Method::head:
          response = get(r, false);
          break;
        case http::Method::options:
        case http::Method::post:
        case http::Method::put:
        case http::Method::delete_:
        case http::Method::trace:
        case http::Method::connect:
          response = getDefaultResponse(http::common_status::ok, "OK");
          break;
        default:
          response = getDefaultResponse(http::common_status::bad_request, "Bad Request");
          break;
      }
    } catch (BadRequestError) {
      response = getDefaultResponse(http::common_status::bad_request, "Bad Request");
    } catch (RequestUriTooLargeError) {
      response = getDefaultResponse(http::common_status::request_uri_too_large, "Request-URI Too Long");
    }
    return _parser.parse(response);
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
      } else
        throw FileNotFound(request.uri);
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
