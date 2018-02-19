/*
** balancer.c for  in c/Socket/UnixSocket/fork_proc_unix
**
** Made by Quentin Albertone
** Login   <albert_q@epitech.net>
**
** Started on  Wed Jan 31 15:15:17 2018 Quentin Albertone
// Last update Mon Feb 19 13:19:50 2018 Jérémy Koehler
*/

int fd_cliGlobal;
int fd_inetGlobal;

# include <sys/un.h>
# include <sys/socket.h>

# include <unistd.h>
# include <stdio.h>

# include <string.h>

# include <netinet/in.h>

#include "HttpInterpreter.hpp"

# define BUFFSIZE 4096
# define _DEBUG_PORT 4242

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

int			main()
{
  char			buff[BUFFSIZE];
  zia::api::HttpInterpreter interpreter(std::map<std::string, std::string>{{"localhost:4242", "./example"}});

  printf("port: %d\n", _DEBUG_PORT);

  fd_inetGlobal = create_socket(_DEBUG_PORT);
  fd_cliGlobal = accept_socket(fd_inetGlobal, _DEBUG_PORT);
  memset(buff, 0, BUFFSIZE);
  while (read(fd_cliGlobal, &buff, BUFFSIZE) > 0)
    {
      /*
      ** DO STUFF
      */
      try {
        std::cerr << "got : " << buff << '\n';
        std::string str = interpreter.interpret(buff);
        str += "\n\0";
        std::cerr << "write : " << str << '\n';
        write(fd_cliGlobal, str.c_str(), str.size());
      } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
      }
      //printf("%s", buff);
      memset(buff, 0, BUFFSIZE);
    }
  close(fd_cliGlobal);
}
