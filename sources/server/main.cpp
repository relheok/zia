//
// main.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 16:42:43 2017 Quentin Albertone
// Last update Tue Feb 20 16:15:38 2018 Jérémy Koehler
//

#include "main.hpp"

/* BEGIN TEST CODE */
int fd_cliGlobal;
int fd_inetGlobal;


# include <sys/un.h>
# include <sys/socket.h>

# include <unistd.h>
# include <stdio.h>

# include <string.h>

# include <netinet/in.h>

# include "http/HttpInterpreter.hpp"
# include "module_manager/ModuleManager.hpp"

# define BUFFSIZE 4096

typedef struct sockaddr_in	t_sockaddr_in;
typedef	struct sockaddr_un	t_sockaddr_un;
typedef struct sockaddr		t_sockaddr;

// Inet Socket part
int			create_socket(int port)
{
  int			fd;
  t_sockaddr_in		addr;

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 3)
    {
      printf("Error socket: %d\n", fd);
      return (fd);
    }
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  if (bind(fd, (t_sockaddr *)&addr, sizeof(t_sockaddr_in)) < 0)
    {
      printf("Error bind\n");
      return (0);
    }
  if (listen(fd, 42))
    {
      printf("Error listen\n");
      return (-10);
    }
  return (fd);
}

int			accept_socket(int fd, int port)
{
  t_sockaddr_in		addr;
  int			fd_cli;
  int			addrlen;

  addrlen = sizeof(addr);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  if ((fd_cli = accept(fd, (t_sockaddr *)&addr, (socklen_t *)&addrlen)) == -1)
    printf("Error accept: %d\n", fd_cli);
  printf("New client fd: %d\n", fd_cli);
  return (fd_cli);
}
/* END TEST CODE */

int		main(int ac, char **av)
{
  try {
    std::string path((ac >= 2) ? (av[1]) : (""));
    zia::api::ConfigManager p(path);
    if (!p.browser_conf())
      std::cerr << "no conf file !" << std::endl;
    //zia::Daemon &daemon = zia::Daemon::getInstance();

    /* BEGIN TEST CODE */
    char			buff[BUFFSIZE];
    zia::api::HttpInterpreter interpreter(std::map<std::string, std::string>{{"localhost:" + std::string(av[2]), "."}}, zia::api::ModulesList());

    printf("port: %d\n", std::stoi(av[2]));

    fd_inetGlobal = create_socket(std::stoi(av[2]));
    fd_cliGlobal = accept_socket(fd_inetGlobal, std::stoi(av[2]));
    memset(buff, 0, BUFFSIZE);
    while (read(fd_cliGlobal, &buff, BUFFSIZE) > 0)
      {
        try {
          std::cout << "\ngot :\n" << buff << '\n';
          std::string str = interpreter.interpret(buff);
          std::cout << "\nwrite :\n" << str << '\n';
          write(fd_cliGlobal, str.c_str(), str.size());
        } catch (std::exception &e) {
          std::cout << e.what() << '\n';
        }
        //printf("%s", buff);
        memset(buff, 0, BUFFSIZE);
      }
    close(fd_cliGlobal);
    close(fd_inetGlobal);
    /* END TEST CODE */

    //start server
    // while (daemon.isAlive()) {
    //   /*
    //   ** TODO
    //   */
    // }

    return (0);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return (-1);
  }
  return (0);
}
