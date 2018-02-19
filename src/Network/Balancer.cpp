//
// Balancer.cpp for  in /home/albert_q/rendu/Tech3/Zia/cpp_zia/src/Network
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Feb  7 14:25:23 2018 Quentin Albertone
// Last update Mon Feb 12 17:51:09 2018 Quentin Albertone
//

#include "Balancer.hpp"

Balancer::Balancer()
  : _nbWorker(_DEBUG_NBWORKER)
{
  createWorker();
  createSocket();
  acceptWorker();
}

Balancer::~Balancer()
{
}

void			Balancer::createSocket()
{
  t_sockaddr_un		addr;

  //write(1, "createSocket \n", 14);
  if ((_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 3)
    {
      _fd = -1;
      return ;
    }
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, SRV_SOCK_PATH);
  if (access(SRV_SOCK_PATH, F_OK) == 0)
    unlink(addr.sun_path);
  if (bind(_fd, (t_sockaddr *)&addr, sizeof(t_sockaddr_un)) < 0)
    {
      printf("Error bind on fd: %d\n", _fd);
      return ;
    }
  if (listen(_fd, SRV_BACKLOG))
    {
      write(2, "Error listen\n", 13);
      return ;
    }
  // printf("listen on fd: %d\n", _fd);
}

int			Balancer::createWorker()
{
  int			i;
  int			pid;

  i = -1;
  //write(1, "createWorker:\n", 14);
  while (++i < _nbWorker)
    {
      if ((pid = fork()) == -1)
	return (write(2, "Create Worker: Error fork\n", 26));
      else if (pid == 0)
	{
	  //	  printf("%d:%d -> %d\n", getppid(), i, getpid());
	  Worker slave(i);
	  slave.loop();
	  exit(1);
	}
      _worker.insert(std::pair<int, int>(i, i));
      usleep(100);
    }
  return (0);
}

void			Balancer::acceptWorker()
{
  int			i;

  i = -1;
  while (++i < _nbWorker)
    if ((_worker[i] = accept(_fd, NULL, NULL)) < 3)
      write(2, "Error: acceptWorker\n", 20);
    // else
    //   printf("%d --> Accept Worker: %d\n", i, _worker[i]);
}

void			Balancer::display()
{
  std::map<int, int>::iterator it = _worker.begin();

  printf("[Balancer:%d] -> fd: %d\n\tsrv_sock_path: %s - _debug_file: %s - _nbWorker: %d\n",
	 getpid(), _fd, SRV_SOCK_PATH, _DEBUG_FILE, _nbWorker);
  for (; it != _worker.end(); ++it)
    printf("\tWorker id: %d - fd: %d\n", it->first, it->second);
}

void			Balancer::sendWorker(char **list)
{
  for (int i = 0; list[i] != NULL; ++i)
    {
      dprintf(_worker[i % _nbWorker], list[i]);
      printf("worker: %d:%d -> %s\n", i % _nbWorker, _worker[i % _nbWorker], list[i]);
    }
}

// int			main(__attribute__((unused))int argc,
// 			     __attribute__((unused))char **argv)
// {
//   Balancer		a;

//   a.display();
//   a.sendWorker(argv);
//   //sleep(7);
// }
