#include "SSLModule.hpp"

extern "C" {
  zia::api::SSLModule *create() {
    return (new zia::api::SSLModule);
  }
}

namespace zia::api {
  SSLModule::SSLModule() : _prio(0) {}

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

  bool SSLModule::exec(HttpDuplex &http) {
    char buf[BUFSIZE];

    _sbio.reset(BIO_new_socket(http.info.sock->s, BIO_NOCLOSE));
    _ssl.reset(SSL_new(_ctx.get()));
    SSL_set_bio(_ssl.get(), _sbio.get(), _sbio.get());
    if (SSL_accept(_ssl.get()) <= 0)
      exitOnError("SSL accept error");

    _io.reset(BIO_new(BIO_f_buffer()));
    _sslbio.reset(BIO_new(BIO_f_ssl()));
    BIO_set_ssl(_sslbio.get(), _ssl.get(), BIO_CLOSE);
    BIO_push(_io.get(), _sslbio.get());

    while (!std::strcmp(buf,"\r\n") || !std::strcmp(buf,"\n")) {
      BIO_gets(_io.get(), buf, BUFSIZE - 1);
    }
    std::cout << "Request: " << buf << std::endl;
    http.resp.reason.clear();
    http.resp.reason.append(buf);
    return (true);
  }

  unsigned int SSLModule::getPriority() const {
    return _prio;
  }

  void  SSLModule::initCtx() {
    const SSL_METHOD  *meth;

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    meth = SSLv23_method();
    _ctx.reset(SSL_CTX_new(meth));
    if (!_ctx.get()) {
      ERR_print_errors_fp(stderr);
      exit(EXIT_FAILURE);
    }
  }

  void SSLModule::loadCertificate() {
    if (!(SSL_CTX_use_certificate_chain_file(_ctx.get(), CERTIFICATE)))
      exitOnError("Cannot use Certificate file: ");
    if (!(SSL_CTX_use_PrivateKey_file(_ctx.get(), PRIVATE_KEY, SSL_FILETYPE_PEM)))
      exitOnError("Cannot use PrivateKey fi, ERR_error_string( ERR_get_error(), NULL )le: ");
    if (!SSL_CTX_load_verify_locations(_ctx.get(), CERTIFICATE, NULL))
      exitOnError("Cannot verify Certificate: ");
  }

  template<typename E>
  void  SSLModule::exitOnError(E e) {
    std::cout << e  << ERR_error_string( ERR_get_error(), NULL ) << std::endl;
    exit(EXIT_FAILURE);
  }
}
