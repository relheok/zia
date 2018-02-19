//
// main.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 16:42:43 2017 Quentin Albertone
// Last update Sun Nov  5 17:00:15 2017 Quentin Albertone
//

#include "SSLModule.hpp"
#include "ModuleLoader.hpp"
#include "module.h"
// #include <unistd.h>

int		main(int argc, char **argv)
{
  // Socket	a(atoi(argv[1]));
  zia::api::ModuleLoader launcher;
  zia::api::Module  *module;
  zia::api::HttpDuplex httpData;

  (void)argc;
  (void)argv;
  try {
    //module = launcher.loadModule("sources/api/modules/test_module.so", "test_module.so");
    module = launcher.loadModule("sources/api/modules/ssl_module.so", "ssl_module.so");
    // module->exec(httpData);
    module->test();
    // sleep(10);
    // module = launcher.reloadModule("sources/api/modules/test_module.so", "test_module.so");
    // module->test();
  } catch (std::exception &e) {
    std::cerr << e.what() << '\n';
    return (1);
  }

  // std::cout << a << std::endl;
  return (0);
}
