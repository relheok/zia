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

int		main(int argc, char **argv)
{
  // Socket	a(atoi(argv[1]));
  zia::api::ModuleLauncher launcher;

  (void)argc;
  (void)argv;
  try {
    launcher.launchModule("sources/api/modules/TestModule.cpp");
  } catch (std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  // std::cout << a << std::endl;
  return (0);
}
