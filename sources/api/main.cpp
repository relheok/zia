//
// main.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 16:42:43 2017 Quentin Albertone
// Last update Sun Nov  5 17:00:15 2017 Quentin Albertone
//

#include "Socket.hpp"

int		main(__attribute__((unused))int argc, char **argv)
{
  Socket	a(atoi(argv[1]));

  std::cout << a << std::endl;
  return (0);
}
