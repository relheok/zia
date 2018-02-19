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
    return true;
  }

  bool SSLModule::exec(HttpDuplex& http) {
    (void)http;
    std::cout << "In exec" << std::endl;
    return true;
  }

  void SSLModule::test() {
    Bio_ptr bio(BIO_new_connect("salut:port"), BIO_free_all);

    if (bio.get() == NULL) {
      std::cout << "Can't create BIO" << std::endl;
    } else if (BIO_do_connect(bio.get()) <= 0) {
      std::cout << "Connection failed" << std::endl;
    }
  }
}
