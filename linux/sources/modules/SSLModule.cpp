#include "SSLModule.hpp"

extern "C" {
  zia::api::SSLModule *create() {
    return (new zia::api::SSLModule);
  }
}

namespace zia::api {
  SSLModule::SSLModule() : _prio(0) {
    _path = getCurrentDir();
    _path = _path.substr(0, _path.find_last_of("/\\")) + "/ressources/";
  }

  SSLModule::SSLModule(SSLModule const &copy) {
    (void)copy;
  }

  SSLModule &SSLModule::operator=(SSLModule const &copy) {
    (void)copy;
    return (*this);
  }

  SSLModule::~SSLModule() {}

  bool SSLModule::config(const Conf &conf) {
    Conf copy = conf;

    try {
      if (copy.find("SSL") == copy.end())
        throw std::logic_error("No SSL config");
      ConfObject obj = std::get<ConfObject>(copy["SSL"].v);
      if (obj.find("cert") == obj.end())
        throw std::logic_error("No certificate");
      _cert = std::get<std::string>(obj["cert"].v);
      if (obj.find("key") == obj.end())
        throw std::logic_error("No key");
      _key = std::get<std::string>(obj["key"].v);
    } catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
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
    if (!(SSL_CTX_use_certificate_chain_file(_ctx.get(), (_path + _cert).c_str())))
      exitOnError("Cannot use Certificate file: ");
    if (!(SSL_CTX_use_PrivateKey_file(_ctx.get(), (_path + _key).c_str(), SSL_FILETYPE_PEM)))
      exitOnError("Cannot use PrivateKey fi, ERR_error_string( ERR_get_error(), NULL )le: ");
    if (!SSL_CTX_load_verify_locations(_ctx.get(), (_path + _cert).c_str(), NULL))
      exitOnError("Cannot verify Certificate: ");
  }

  std::string SSLModule::getCurrentDir() {
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    return std::string( result, (count > 0) ? count : 0 );
  }

  template<typename E>
  void  SSLModule::exitOnError(E e) {
    std::cerr << e << ERR_error_string( ERR_get_error(), NULL ) << '\n';
    exit(EXIT_FAILURE);
  }
}
