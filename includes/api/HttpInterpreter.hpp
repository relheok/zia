#ifndef HTTPINTERPRETER_HPP_
# define HTTPINTERPRETER_HPP_

# include <iostream>
# include <string>
# include <ctime>
# include "http.h"
# include "Utils.hpp"
# include "module.h"
# include "Constant.hpp"
# include "HttpParser.hpp"
# include "HtmlManager.hpp"

namespace zia::api {
  class   HttpInterpreter {
  public:
    /**
    * [roots] : the roots directory as ("host","root")
    * [module] : the PHP module
    */
    HttpInterpreter(std::map<std::string, std::string> const &root, Module *php = nullptr);
    HttpInterpreter(HttpInterpreter const &);
    HttpInterpreter   &operator=(HttpInterpreter const &);
    ~HttpInterpreter();

    /**
    * Interpret the request [request]
    * \return the formatted HTTP Response
    */
    std::string         interpret(std::string const &request);

    /**
    * Create a default HttpResponse with [status] and [reason] (has to be format with this._parser.parse(HttpResponse))
    * \return the response
    */
    static struct HttpResponse getDefaultResponse(http::Status const &status = http::common_status::unknown, std::string const &reason = "");

    /**
    * Setters
    */
    void                setRoots(std::map<std::string, std::string> const &roots) { _roots = roots; }

    /**
    * Getters
    */
    std::map<std::string, std::string>  getRoots() const { return _roots; }

    static Net::Raw            getBody(std::string const &);

    HttpParser          _parser;
  private:
    struct HttpResponse get(struct HttpRequest const &request, bool body = true);

    std::string         getRootFromHost(std::map<std::string, std::string> const &);

    std::map<std::string, std::string>  _roots;
    std::map<std::string, std::string>  _mimeType;
    Module                              *_php;
  };
} /* zia::api */

#endif /* end of include guard: HTTPINTERPRETER_HPP_ */
