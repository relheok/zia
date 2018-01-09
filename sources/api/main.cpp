//
// main.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 16:42:43 2017 Quentin Albertone
// Last update Sun Nov  5 17:00:15 2017 Quentin Albertone
//

#include "ModuleLauncher.hpp"
#include "TestModule.hpp"

int		main(int argc, char **argv)
{
  // Socket	a(atoi(argv[1]));
  zia::api::ModuleLauncher launcher;
  zia::api::TestModule  *module;

  (void)argc;
  (void)argv;
  try {
    module = (zia::api::TestModule*)launcher.launchModule("sources/api/modules/test_module.so", "test_module.so");
    module->config();
  } catch (std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  // std::cout << a << std::endl;
  return (0);
}
