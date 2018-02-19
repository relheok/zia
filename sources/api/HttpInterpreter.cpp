#include "HttpInterpreter.hpp"

namespace zia::api {
  HttpInterpreter::HttpInterpreter(std::map<std::string, std::string> const &roots, Module *php) : _roots(roots), _php(php) {
    _mimeType = {
      {"avi","video/x-msvideo"},
      {"bin","application/octet-stream"},
      {"css","text/css"},
      {"csv","text/csv"},
      {"doc","application/msword"},
      {"gif","image/gif"},
      {"htm","text/html; charset=UTF-8"},
      {"html","text/html; charset=UTF-8"},
      {"ico","image/x-icon"},
      {"jar","application/java-archive"},
      {"jpeg","image/jpeg"},
      {"jpg","image/jpeg"},
      {"js","application/javascript"},
      {"json","application/json"},
      {"mpeg","video/mpeg"},
      {"otf","font/otf"},
      {"png","image/png"},
      {"pdf","application/pdf"},
      {"rar","application/x-rar-compressed"},
      {"rtf","application/rtf"},
      {"sh","application/x-sh"},
      {"svg","image/svg+xml"},
      {"swf","application/x-shockwave-flash"},
      {"tar","application/x-tar"},
      {"wav","audio/x-wav"},
      {"xhtml","application/xhtml+xml"},
      {"xml","application/xml"},
      {"zip","application/zip"}
    };
  }

  HttpInterpreter::HttpInterpreter(HttpInterpreter const &original) {
    _roots = original._roots;
    _parser = original._parser;
  }

  HttpInterpreter   &HttpInterpreter::operator=(HttpInterpreter const &original) {
    _roots = original._roots;
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
          response = getDefaultResponse(r, http::common_status::ok, "OK");
          break;
        default:
          response = getDefaultResponse(r, http::common_status::bad_request, "Bad Request");
          break;
      }
    } catch (BadRequestError &e) {
      std::cerr << e.what() << '\n';
      response = getDefaultResponse(r, http::common_status::bad_request, "Bad Request");
    } catch (RequestUriTooLargeError &e) {
      std::cerr << e.what() << '\n';
      response = getDefaultResponse(r, http::common_status::request_uri_too_large, "Request-URI Too Long");
    }
    return _parser.parse(response);
  }

  struct HttpResponse   HttpInterpreter::getDefaultResponse(struct HttpRequest &req, http::Status const &status, std::string const &reason) {
    struct HttpResponse response;
    time_t              t = std::time(nullptr);

    response.version = http::Version::http_1_1;
    response.status = status;
    response.reason = reason;
    char buf[42];
    std::strftime(buf, 42, "%a, %d %b %Y %H:%M:%S GMT", std::gmtime(&t));
    response.headers["Date"] = buf;
    response.headers["Server"] = SERVER_NAME + std::string("/") + SERVER_VERSION;
    if (req.headers.find("Cookie") != req.headers.end())
      response.headers["Cookie"] = req.headers["Cookie"];
    return response;
  }

  struct HttpResponse         HttpInterpreter::get(struct HttpRequest &request, bool body) {
    struct HttpResponse       response;
    std::vector<std::string>  v = Utils::split(request.uri, "?");
    HttpDuplex                duplex;

    try {
      duplex.req = request;
      duplex.resp = getDefaultResponse(request, http::common_status::ok, "OK");
      std::string path = getRootFromHost(request.headers) + request.uri;
      response = getDefaultResponse(request, http::common_status::ok, "OK");
      if (_mimeType.find(Utils::getExtension(v[0])) != _mimeType.end()) {
        response.body = getBody(Utils::readFile(path));
        response.headers["Content-Type"] = _mimeType[Utils::getExtension(v[0])];
        response.headers["Content-Length"] = std::to_string(response.body.size());
        if (!body)
          response.body.clear();
      } else if (Utils::getExtension(v[0]).compare("php") == 0) {
        if (!_php)
          throw BadRequestError("php isn't supported");
        _php->exec(duplex);
        return duplex.resp;
      } else if (Utils::isDirectory(path)) {
        response = getDefaultResponse(request, http::common_status::ok, "OK");
        response.body = getBody(HtmlManager::viewDirectory(path, request.uri));
        response.headers["Content-Type"] = _mimeType["html"];
        response.headers["Content-Length"] = std::to_string(response.body.size());
        return response;
      } else
        throw FileNotFound(request.uri);
    } catch (FileNotFound &e) {
      std::cerr << e.what() << '\n';
      return getDefaultResponse(request, http::common_status::not_found, "Not found");
    } catch (BadRequestError &e) {
      std::cerr << e.what() << '\n';
      return getDefaultResponse(request, http::common_status::bad_request, "Bad Request");
    } catch (std::exception &e) {
      std::cerr << e.what() << '\n';
      return getDefaultResponse(request, http::common_status::internal_server_error, "Internal Server Error");
    }
    return response;
  }

  Net::Raw    HttpInterpreter::getBody(std::string const &str) {
    Net::Raw  body;

    for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
      body.push_back(std::byte(*it));
    return body;
  }

  std::string   HttpInterpreter::getRootFromHost(std::map<std::string, std::string> const &headers) {
    auto ith = headers.find("Host");

    if (ith == headers.end())
      throw BadRequestError("no Host header");
    auto itr = _roots.find(ith->second);
    if (itr == _roots.end())
      throw BadRequestError("the specified host '" + ith->second + "' hasn't been found");
    return itr->second;
  }
} /* zia:api */
