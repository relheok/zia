#include "phpcpp.hpp"
#include <unistd.h>
#include <cstring>
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
  std::cerr << "Config PHP Module" << '\n';
  std::cout << "Content-type:text/html\r\n\r\n";
  std::cout << "<html>\n";
  std::cout << "<head>\n";
  std::cout << "<title>CGI Environment Variables</title>\n";
  std::cout << "</head>\n";
  std::cout << "<body>\n";
  std::cout << "<table border = \"0\" cellspacing = \"2\">";

  for (int i = 0; i < 24; i++) {
    std::cout << "<tr><td>" << _env[i] << "</td><td>";
    // attempt to retrieve value of environment variable
    char *value = getenv(_env[i].c_str() );  
    if ( value != 0 ) {
      std::cout << value;                                 
    }
    else {
      std::cout << "Environment variable does not exist.";
    }
    std::cout << "</td></tr>\n";
  }
  std::cout << "</table><\n";
  std::cout << "</body>\n";
  std::cout << "</html>\n";
  (void)conf;
  getpost_test();
  return (true);
}

bool	zia::api::cppModule::exec(HttpDuplex& http) {
  (void)http;
  return (true);
}
