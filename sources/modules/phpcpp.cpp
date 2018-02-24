#include "phpcpp.hpp"
#include <unistd.h>
#include <cstring>
#include <sstream>
#include "getpost.hpp"

extern "C" {
  zia::api::cppModule *create() {
    return (new zia::api::cppModule);
  }
}

zia::api::cppModule::cppModule() {
  initComponent();
}

zia::api::cppModule::cppModule(const zia::api::cppModule &copy) {
  (void)copy;
}

zia::api::cppModule &zia::api::cppModule::operator=(const zia::api::cppModule &copy) {
  (void)copy;
  return (*this);
}

zia::api::cppModule::~cppModule() {}

bool  zia::api::cppModule::initComponent() {
  return (true);
}

bool	zia::api::cppModule::config(const Conf& conf) {
  auto it = conf.find("PHP");
  if (it != conf.end())
    return (true);
  else
    std::cerr << "No conf file for php module :(" << std::endl;
  return (false);
}

bool	zia::api::cppModule::exec(HttpDuplex& http) {
  http.resp.body = stringToRaw(http.req.body);
  http.resp.headers["Content-Length"] = std::to_string(http.resp.body.size());
  http.resp.headers["Content-Type"] = "text/html; char-set=UTF=8";
  return (true);
}

zia::api::Net::Raw    zia::api::cppModule::stringToRaw(Net::Raw req) {
  Net::Raw  r;
  r = req;
  return (r);
}
