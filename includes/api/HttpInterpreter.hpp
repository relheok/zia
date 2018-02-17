#ifndef HTTPINTERPRETER_HPP_
# define HTTPINTERPRETER_HPP_

#include <iostream>
#include <string>
#include <ctime>
#include "http.h"
#include "Utils.hpp"
#include "Constant.hpp"
#include "HttpParser.hpp"

namespace zia::api {
  class   HttpInterpreter {
  public:
    /**
    * [root] : the root directory
    */
    HttpInterpreter(std::string const &root);
    HttpInterpreter(HttpInterpreter const &);
    HttpInterpreter   &operator=(HttpInterpreter const &);
    ~HttpInterpreter();

    /**
    * Interpret the request [request]
    * \return the formatted HTTP Response
    */
    std::string           interpret(std::string const &request);

    /**
    * Setters
    */
    void                  setRoot(std::string const &root) { _root = root; }

    /**
    * Getters
    */
    std::string           getRoot() const { return _root; }

  private:
    struct HttpResponse   getDefaultResponse(http::Status const &status = http::common_status::unknown, std::string const &reason = "");
    struct HttpResponse   get(struct HttpRequest const &request, bool body = true);

    Net::Raw              getBody(std::string const &);

    std::string           _root;
    HttpParser            _parser;
  };
} /* zia::api */

#endif /* end of include guard: HTTPINTERPRETER_HPP_ */
