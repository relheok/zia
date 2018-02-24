#include "phpcpp.hpp"
#include <unistd.h>
#include <sys/wait.h>
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

std::string   rawToString(zia::api::Net::Raw const &r) {
  std::string str;

  for (auto it = r.begin(); it != r.end(); it++)
    str += (char)*it;
  return str;
}

zia::api::Net::Raw      zia::api::cppModule::stringToRaw(std::string const &str) {
  zia::api::Net::Raw    r;

  for (auto it = str.begin(); it != str.end(); it++)
    r.push_back(std::byte(*it));
  return r;
}

bool		zia::api::cppModule::exec(HttpDuplex& http) {
  Net::Raw	net;
  int		link[2];
  pid_t		pid;
  char		foo[4096 + 1];
  int		nbytes = 0;
  std::string	totalStr;
  memset(foo, 0, 4096);
  if (pipe(link)==-1)
    return (false);
  if ((pid = fork()) == -1)
    return (false);
  if(pid == 0) {
    dup2(link[1], STDOUT_FILENO);
    close(link[0]);
    close(link[1]);
    execl("/usr/bin/php-cgi", "-q --no-header", "./example/example.html", (char *)0);
    return (false);
  }
  else {
    close(link[1]);
    while(0 != (nbytes = read(link[0], foo, sizeof(foo)))) {
      totalStr = totalStr + foo;
      printf("Output: %.*s\n", nbytes, foo);
      http.resp.body = stringToRaw(foo);
      http.resp.headers["Content-Type"] = "text/html; charset=UTF-8";
      http.resp.headers["Content-Length"] = std::to_string(http.resp.body.size());
      memset(foo, 0, 4096);
    }
    wait(NULL);
  }
  return (true);
}
