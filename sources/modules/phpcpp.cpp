#include "phpcpp.hpp"
#include <unistd.h>
#include <cstring>

zia::api::cppModule::cppModule() {
  std::string tmp("cppModule");
  _name = tmp;
  initComponent();
}

zia::api::cppModule::cppModule(const zia::api::cppModule &copy) {
  _ptr.reset(new zia::api::cppModule(*(copy._ptr.get())));
  _name = copy.getName();
}

zia::api::cppModule &zia::api::cppModule::operator=(const zia::api::cppModule &copy) {
  _ptr.reset(new zia::api::cppModule(*(copy._ptr.get())));
  _name = copy.getName();
  return (*this);
}

zia::api::cppModule::~cppModule() {}

bool  zia::api::cppModule::initComponent() {
  char				**sysCline = NULL;
  char				**sysEnv = NULL;
  std::string			sData = "var_1=val_1&var_2=val_2";
  std::vector<std::string>	aEnv; 
  std::vector<std::string>	aArgs;

  _ptr.reset(new zia::api::cppModule);
  aArgs.push_back("/usr/bin/php-cgi");
  aArgs.push_back("/test.php");

  aEnv.push_back("GATEWAY_INTERFACE=CGI/1.1");
  aEnv.push_back("SERVER_PROTOCOL=HTTP/1.1");
  aEnv.push_back("QUERY_STRING=test=querystring");
  aEnv.push_back("REDIRECT_STATUS=200");
  aEnv.push_back("REQUEST_METHOD=POST");
  aEnv.push_back("CONTENT_TYPE=application/x-www-form-urlencoded;charset=utf-8");
  aEnv.push_back("SCRIPT_FILENAME=/test.php");
  aEnv.push_back("CONTENT_LENGTH="+ std::to_string(sData.length()) );

  sysCline = new char*[aArgs.size() + 1];
  for (size_t i = 0; i < aArgs.size(); i++) {
    sysCline[i] = new char[aArgs[i].size()+1];
    strncpy(sysCline[i], aArgs[i].c_str(), aArgs[i].size()+1);
  }
  sysCline[aArgs.size()] = NULL;
  
  sysEnv = new char*[aEnv.size() + 1];
  for (size_t i = 0; i < aEnv.size(); i++) {
    sysEnv[i] = new char[aEnv[i].size()+1];
    strncpy(sysEnv[i], aEnv[i].c_str(), aEnv[i].size() + 1);
  }
  sysEnv[aEnv.size()] = NULL;
  execve(sysCline[0], sysCline, sysEnv);
  return (true);
}

std::string   zia::api::cppModule::getName() const {
  return (_name);
}

void    zia::api::cppModule::setName(std::string const &name) {
  _name = name;
}

bool	zia::api::cppModule::config(const Conf& conf) {
  (void)conf;
  return (true);
}

bool	zia::api::cppModule::exec(HttpDuplex& http) {
  (void)http;
  return (true);
}

extern "C" {
  zia::api::cppModule *createcpp() {
    return (new zia::api::cppModule);
  }
}
