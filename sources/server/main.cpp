//
// main.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 16:42:43 2017 Quentin Albertone
// Last update Sun Nov  5 17:00:15 2017 Quentin Albertone
//

#include "main.hpp"

int		main(int ac, char **av)
{
  try 
  {
    std::string path((ac == 2) ? (av[1]) : (""));
    zia::api::ConfigManager p(path);
    if (ac >= 2 && p.browser_conf() == true)
    {
       zia::api::ModuleManager launcher;

      //start server
      return (0);
    }
    else
    {
      std::cout << "no conf file !" << std::endl;
      zia::api::ModuleManager launcher;
      // start server with default value
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return (-1);
  }
  return (0);
}
    // sleep(10);
    // module = launcher.reloadModule("sources/api/modules/test_module.so", "test_module.so");
    // module->test();
