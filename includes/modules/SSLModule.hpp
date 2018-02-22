#ifndef SSLMODULE_HPP_
# define SSLMODULE_HPP_

# include <iostream>
# include <memory>
# include "conf.h"
# include "IModule.hpp"
# include "http.h"

# include "openssl/bio.h"
# include "openssl/ssl.h"
# include "openssl/err.h"

#include <cstring>

typedef zia::api::Module *(*myModule)();

#define PRIVATE_KEY "key.pem"
#define CERTIFICATE "cert.pem"
#define BUFSIZE 1024

namespace zia::api {
  class SSLModule : public IModule {
  public:
    SSLModule();
    SSLModule(SSLModule const &);
    SSLModule &operator=(SSLModule const &);
    virtual ~SSLModule();

    virtual bool config(const Conf &conf);
    virtual bool exec(HttpDuplex &http);

    virtual unsigned int getPriority() const { return 0; }

  private:
    BIO       *_sbio;
    BIO       *_io;
    BIO       *_sslbio;
    SSL       *_ssl;
    SSL_CTX   *_ctx;

    void      initCtx();
    void      loadCertificate();
    template<typename E>
    void      exitOnError(E e);
  };
}

using Bio_ptr = std::unique_ptr<BIO, decltype(&BIO_free_all)>;

#endif /* end of include guard: SSLMODULE_HPP_ */
