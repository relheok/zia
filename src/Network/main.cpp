//
// main.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 16:42:43 2017 Quentin Albertone
// Last update Mon Feb 12 17:53:59 2018 Quentin Albertone
//

#include "Network.hpp"

int		main(__attribute__((unused))int argc, __attribute__((unused))char **argv)
{
  Network::Socket	inet(atoi(argv[1]));
  RequestList		req();
  //Balancer		pipe;

  //pipe.display();
  while (true)
    {
      inet.loop();
      inet.displayRequest();
      //      req = inet.getReq();
      sleep(3);
      std::cout << "\n----------------------------" << std::endl;
    }
  return (0);
}
