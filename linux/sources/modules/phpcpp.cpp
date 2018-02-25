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

zia::api::cppModule::cppModule() {}

zia::api::cppModule::cppModule(const zia::api::cppModule &copy) {
  (void)copy;
}

zia::api::cppModule &zia::api::cppModule::operator=(const zia::api::cppModule &copy) {
  (void)copy;
  return (*this);
}

zia::api::cppModule::~cppModule() {}

bool	zia::api::cppModule::config(const Conf& conf) {
  auto it = conf.find("PHP");
  if (it != conf.end())
    return (true);
  return (false);
}

std::string   zia::api::cppModule::rawToString(zia::api::Net::Raw const &r) {
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
  std::vector<std::string> vGet = split(rawToString(http.raw_req), "?");
  std::string   url = vGet[0];
  std::string   args = "";

  if (http.req.method == http::Method::post) {
    args = rawToString(http.req.body);
  } else if (http.req.method == http::Method::get) {
    args = (vGet.size() > 1 ? vGet[1] : "");
  }
  return (execRequest(http, url, args));
}

bool          zia::api::cppModule::execRequest(HttpDuplex& http, std::string &url, std::string &args) {
  int		link[2];
  char		foo[4096 + 1];
  int		nbytes = 0;
  pid_t		pid;
  std::string	totalStr;

  if (split(url, ".").back().compare("php") == 0
    || split(url, ".").back().compare("html") == 0
    || split(url, ".").back().compare("htm") == 0) {
    memset(foo, 0, 4096);
    if (pipe(link) == -1)
      return false;
    if ((pid = fork()) == -1)
      return (false);
    if(pid == 0) {
      dup2(link[1], STDOUT_FILENO);
      close(link[0]);
      close(link[1]);
      execv("/usr/bin/php-cgi", getArgs(url, args));
      exit(0);
    } else {
      close(link[1]);
      while(0 != (nbytes = read(link[0], foo, sizeof(foo)))) {
      	totalStr = totalStr + foo;
      	http.resp.body = stringToRaw(foo);
      	http.resp.headers["Content-Type"] = "text/html; charset=UTF-8";
      	http.resp.headers["Content-Length"] = std::to_string(http.resp.body.size());
      	memset(foo, 0, 4096);
      }
      wait(NULL);
    }
    return (true);
  }
  return true;
}

char                      **zia::api::cppModule::getArgs(std::string &url, std::string &args) {
  std::vector<std::string> v = split(args, "&");
  char      **argv = new char*[v.size() + 3];
  int       i = 2;

  argv[0] = strdup("-q");
  argv[1] = strdup(url.c_str());
  if (!v.empty()) {
    for (auto it = v.begin(); it != v.end(); ++it) {
      argv[i] = strdup(it->c_str());
      i++;
    }
  }
  argv[i] = NULL;
  return argv;
}

std::vector<std::string>    zia::api::cppModule::split(std::string const &str, std::string const &delimiters) {
  std::vector<std::string>  v;
  char                      *tmp;
  char                      *toFree = strdup(str.c_str());

  tmp = strtok(toFree, delimiters.c_str());
  while (tmp != NULL) {
    v.push_back(tmp);
    tmp = strtok(NULL, delimiters.c_str());
  }
  free(toFree);
  return v;
}
