#ifndef SSLMODULE_HPP_
# define SSLMODULE_HPP_

# include <iostream>
# include <memory>
# include "conf.h"
# include "module.h"
# include "http.h"

# include "openssl/bio.h"
# include "openssl/ssl.h"
# include "openssl/err.h"

typedef zia::api::Module *(*myModule)();

namespace zia::api {
  class SSLModule : public Module {
  public:
    SSLModule();
    SSLModule(SSLModule const &);
    SSLModule &operator=(SSLModule const &);
    virtual ~SSLModule();

    virtual bool config(const Conf &conf);
    virtual bool exec(HttpDuplex &http);
    virtual void test();
  };
}

using Bio_ptr = std::unique_ptr<BIO, decltype(&BIO_free_all)>;

#endif /* end of include guard: SSLMODULE_HPP_ */
