#include "TestModule.hpp"

namespace zia::api {
  TestModule::TestModule() {}

  TestModule::TestModule(TestModule const &copy) {
    (void)copy;
  }

  TestModule  &TestModule::operator=(TestModule const &copy) {
    (void)copy;
    return (*this);
  }

  TestModule::~TestModule() {}

  bool TestModule::config(const Conf &conf) {
    (void)conf;
    std::cerr << "config" << '\n';
    return false;
  }

  bool TestModule::exec(HttpDuplex& http) {
    (void)http;
    std::cerr << "exec" << '\n';
    return true;
  }
}
