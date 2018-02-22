#ifndef SSLMODULE_HPP_
# define SSLMODULE_HPP_

#include <cstring>
# include <iostream>
# include <memory>

# include "conf.h"
# include "http.h"
# include "IModule.hpp"

# include "openssl/bio.h"
# include "openssl/ssl.h"
# include "openssl/err.h"

typedef zia::api::Module *(*myModule)();

#define PRIVATE_KEY "key.pem"
#define CERTIFICATE "cert.pem"
#define BUFSIZE 1024

using Ssl_ptr = std::unique_ptr<SSL, decltype(&SSL_free)>;
using Bio_ptr = std::unique_ptr<BIO, decltype(&BIO_free_all)>;
using Ctx_ptr = std::unique_ptr<SSL_CTX, decltype(&SSL_CTX_free)>;

namespace zia::api {
  class SSLModule : public IModule {
  public:
    SSLModule();
    SSLModule(SSLModule const &);
    SSLModule &operator=(SSLModule const &);
    virtual ~SSLModule();

    virtual bool config(const Conf &conf);
    virtual bool exec(HttpDuplex &http);
    virtual unsigned int getPriority() const;

  private:
    Bio_ptr       _sbio{NULL, BIO_free_all};
    Bio_ptr       _io{NULL, BIO_free_all};
    Bio_ptr       _sslbio{NULL, BIO_free_all};
    Ctx_ptr       _ctx{NULL, SSL_CTX_free};
    Ssl_ptr       _ssl{NULL, SSL_free};
    unsigned int  _prio;

    void          initCtx();
    void          loadCertificate();
    template<typename E>
    void          exitOnError(E e);
  };
}

#endif /* end of include guard: SSLMODULE_HPP_ */
