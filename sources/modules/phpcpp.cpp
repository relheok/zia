#include "phpcpp.hpp"
#include <unistd.h>
#include <cstring>
#include "getpost.h"

int getpost_test();

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

int	getpost_test() {
  std::map<std::string, std::string> Get;
  initializeGet(Get);
  std::cout<< "Content-type: text/html" << std::endl << std::endl;
  std::cout<< "<html><body>" << std::endl;
  std::cout<< "<h1>Try post and get method</h1>" << std::endl;
  std::cout<< "<form method=\"get\">" << std::endl;
  std::cout<< " <label for=\"fname\">First name: </label>" << std::endl;
  std::cout<< " <input type=\"text\" name=\"fname\" id=\"fname\"><br>" << std::endl;
  std::cout<< " <label for=\"lname\">Last name: </label>" << std::endl;
  std::cout<< " <input type=\"text\" name=\"lname\" id=\"lname\"><br>" << std::endl;
  std::cout<< " <input type=\"submit\" />" << std::endl;
  std::cout<< "</form><br /><br />" << std::endl;
  if (Get.find("fname")!=Get.end() && Get.find("lname")!=Get.end()) {
    std::cout << "Hello " << Get["fname"] << " " << Get["lname"]
	      << ", I guess php-cgi module works" << std::endl;
  }
  else {
    std::cout << "Fill up the above from and press submit" << std::endl;
  }
  std::cout << "</body></html>" << std::endl;
  return (0);
}

bool	zia::api::cppModule::exec(HttpDuplex& http) {
  (void)http;
  return (true);
}
