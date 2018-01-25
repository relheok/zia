//
// main.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 16:42:43 2017 Quentin Albertone
// Last update Sun Nov  5 17:00:15 2017 Quentin Albertone
//

#include "config_manager/ConfigManager.hpp"
#include "ModuleLoader.hpp"
#include "module.h"
// #include <unistd.h>

int		main(int ac, char **av)
{
  zia::api::ModuleManager launcher;
  zia::api::Module  *module;

  try {
    std::string path((ac == 2) ? (av[1]) : (""));
    zia::api::ConfigManager p(path);
    if (ac == 2)
    {
      try
      {
        p.CheckPath();
        module = launcher.loadModule("sources/modules/test_module.so", "test_module.so");
        module->test();
      }
      catch (std::exception &err)
      {
        std::cerr << err.what() << std::endl;
        // call the last method of parsing for launch conf with default value
        return (2);
      }
    }
    else
    {
      std::cout << "no conf file !" << std::endl;
      // call the last method of parsing for launch conf with default value
    }
    // sleep(10);
    // module = launcher.reloadModule("sources/api/modules/test_module.so", "test_module.so");
    // module->test();
  } catch (std::exception &e) {
    std::cerr << e.what() << '\n';
    return (1);
  }
	return (0);
}
