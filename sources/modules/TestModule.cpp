#include "TestModule.hpp"

extern "C" {
  zia::api::TestModule   *create() {
    return (new zia::api::TestModule);
  }
}

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
    return true;
  }

  bool TestModule::exec(HttpDuplex& http) {
    (void)http;
    return true;
  }

  void TestModule::test() {
    std::cerr << "TestModule::test" << '\n';
  }
}
