#include "SSLModule.hpp"

extern "C" {
  zia::api::SSLModule *create() {
    return (new zia::api::SSLModule);
  }
}

namespace zia::api {
  SSLModule::SSLModule() {}

  SSLModule::SSLModule(SSLModule const &copy) {
    (void)copy;
  }

  SSLModule &SSLModule::operator=(SSLModule const &copy) {
    (void)copy;
    return (*this);
  }

  SSLModule::~SSLModule() {}

  bool SSLModule::config(const Conf &conf) {
    (void)conf;
    initCtx();
    loadCertificate();
    return (true);
  }

  bool SSLModule::exec(HttpDuplex& http) {
    char buf[BUFSIZE];

    _sbio = BIO_new_socket(http.info.sock->s, BIO_NOCLOSE);
    _ssl = SSL_new(_ctx);
    SSL_set_bio(_ssl, _sbio, _sbio);
    if (SSL_accept(_ssl) <= 0)
      exitOnError("SSL accept error");

    _io = BIO_new(BIO_f_buffer());
    _sslbio = BIO_new(BIO_f_ssl());
    BIO_set_ssl(_sslbio, _ssl, BIO_CLOSE);
    BIO_push(_io, _sslbio);

    while (!std::strcmp(buf,"\r\n") || !std::strcmp(buf,"\n")) {
      BIO_gets(_io, buf, BUFSIZE - 1);
    }
    std::cout << "Request: " << buf << std::endl;
    http.resp.reason.clear();
    http.resp.reason.append(buf);
    return (true);
  }

  void  SSLModule::initCtx() {
    const SSL_METHOD  *meth;

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    meth = SSLv23_method();
    if (!(_ctx = SSL_CTX_new(meth))) {
      ERR_print_errors_fp(stderr);
      exit(EXIT_FAILURE);
    }
  }

  void SSLModule::loadCertificate() {
    if (!(SSL_CTX_use_certificate_chain_file(_ctx, CERTIFICATE)))
      exitOnError("Cannot use Certificate file: ");
    if (!(SSL_CTX_use_PrivateKey_file(_ctx, PRIVATE_KEY, SSL_FILETYPE_PEM)))
      exitOnError("Cannot use PrivateKey fi, ERR_error_string( ERR_get_error(), NULL )le: ");
    if (!SSL_CTX_load_verify_locations(_ctx, CERTIFICATE, NULL))
      exitOnError("Cannot verify Certificate: ");
  }

  template<typename E>
  void  SSLModule::exitOnError(E e) {
    std::cout << e  << ERR_error_string( ERR_get_error(), NULL ) << std::endl;
    exit(EXIT_FAILURE);
  }
}
