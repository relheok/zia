#ifndef CPPMODULE_HPP_
# define CPPMODULE_HPP_

# include <iostream>
# include <memory>
# include "IModule.hpp"
# include "http.h"
# include "conf.h"
# include "net.h"

namespace zia::api {
  class     cppModule : public IModule {
  public:
    cppModule();
    cppModule(const cppModule &);
    cppModule &operator=(const cppModule &);
    ~cppModule();

    bool          initComponent();
    virtual bool  config(const Conf& conf);
    virtual bool  exec(HttpDuplex& http);

    virtual unsigned int getPriority() const { return 1; }
  private:
const std::string _env[24] = {
   "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",
   "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",
   "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",
   "HTTP_HOST", "HTTP_USER_AGENT", "PATH",
   "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",
   "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
   "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",
   "SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",
   "SERVER_SIGNATURE","SERVER_SOFTWARE" };
  };
}

#endif /* end of include guard: CPPMODULE_HPP_ */
