//
// main.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 16:42:43 2017 Quentin Albertone
// Last update Mon Jan 29 16:08:35 2018 Quentin Albertone
//

#include "Network.hpp"
//#include "Client.hpp"

int		main(__attribute__((unused))int argc, __attribute__((unused))char **argv)
{
  Network::Socket	a(atoi(argv[1]));
  RequestList		b();

  while (true)
    {
      a.loop();
      //b.displayRequest();
    }
  return (0);
}
