//
// Balancer.cpp for  in /home/albert_q/rendu/Tech3/Zia/cpp_zia/src/Network
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Feb  7 14:25:23 2018 Quentin Albertone
// Last update Wed Feb 21 21:30:31 2018 Quentin Albertone
//

#include "Balancer.hpp"
#include "logger.hpp"

Balancer::Balancer()
  : _nbWorker(_DEBUG_NBWORKER)
{
  _daemon = &zia::Daemon::getInstance();
  zia::Logger::getInstance().info("Ctr Balancer");
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

  if ((_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 1)
    {
      _fd = -1;
      zia::Logger::getInstance().error("[BALANCER] - Failed to create unix socket");
      return ;
    }
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, SRV_SOCK_PATH);
  if (access(SRV_SOCK_PATH, F_OK) == 0)
    unlink(addr.sun_path);
  if (bind(_fd, (t_sockaddr *)&addr, sizeof(t_sockaddr_un)) < 0)
    {
      // printf("Error bind on fd: %d\n", _fd);
      zia::Logger::getInstance().error("[BALANCER] Failed to bind fd");
      return ;
    }
  if (listen(_fd, SRV_BACKLOG))
    {
      zia::Logger::getInstance().error("[BALANCER] Failed to listen");
      // write(2, "Error listen\n", 13);
      return ;
    }
}

int			Balancer::createWorker()
{
  int			i;
  int			pid;

  i = -1;
  zia::Logger::getInstance().error("[BALANCER] - Create Worker begining - _nbWorker:" + std::to_string(_nbWorker));
  while (++i < _nbWorker)
    {
      if ((pid = fork()) == -1)
	{
	  zia::Logger::getInstance().error("[BALANCER] - Create Worker: Error fork");
	  // write(2, "Create Worker: Error fork\n", 26);
	  return (1);
	}
      else if (pid == 0)
	{
	  zia::Logger::getInstance().info("[BALANCER] - Create Worker: child process");
	  Worker slave(i, _daemon);
	  slave.loop();
	  exit(1);
	}
      else
	zia::Logger::getInstance().error("[BALANCER] - Create Worker " + std::to_string(i) + " pid : " + std::to_string(pid));
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
      zia::Logger::getInstance().info("[BALANCER] - Accept Worker");
      //write(2, "Error: acceptWorker\n", 20);
}

// void			Balancer::display()
// {
//   std::map<int, int>::iterator it = _worker.begin();

//   zia::Logger::getInstance().error("[BALANCER] - Create Worker: Error fork");
//   printf("[Balancer:%d] -> fd: %d\n\tsrv_sock_path: %s - _debug_file: %s - _nbWorker: %d\n",
// 	 getpid(), _fd, SRV_SOCK_PATH, _DEBUG_FILE, _nbWorker);
//   for (; it != _worker.end(); ++it)
//     printf("\tWorker id: %d - fd: %d\n", it->first, it->second);
// }

int			Balancer::sendToWorker(int workerFd, int clientFd)
{
  struct msghdr		msg;
  char			buff[CMSG_SPACE(sizeof(clientFd))];
  struct iovec  	iov = {.iov_base = ((char *)"zia"), .iov_len = 3};

  memset(&msg, 0, sizeof(struct msghdr));
  memset(buff, 0, sizeof(buff));
  msg.msg_iov = &iov;
  msg.msg_iovlen = 1;
  msg.msg_control = buff;
  msg.msg_controllen = sizeof(buff);

  struct cmsghdr	*cmsg = CMSG_FIRSTHDR(&msg);
  cmsg->cmsg_level = SOL_SOCKET;
  cmsg->cmsg_type = SCM_RIGHTS;
  cmsg->cmsg_len = CMSG_LEN(sizeof(clientFd));

  *(int*) CMSG_DATA(cmsg) = clientFd;

  msg.msg_controllen = cmsg->cmsg_len;

  if (sendmsg(workerFd, &msg, 0) < 0)
    {
      zia::Logger::getInstance().error("[BALANCER] - Failed communicate with worker:" + std::to_string(workerFd));
      return (-1); //printf("Failed communicate with worker:%2d\n", workerFd));
    }
  zia::Logger::getInstance().error("[BALANCER] - Send fd:" + std::to_string(clientFd) + "to worker:" + std::to_string(workerFd));
  //printf("Send fd:%d to worker:%d\n", clientFd, workerFd);
  usleep(100);
  // while (read(clientFd, buff, sizeof(clientFd)) == sizeof(clientFd))
  //   {
  //     printf("%s\n", buff);
  //   }
  return (0);
}

int			Balancer::balancer(RequestList &req)
{
  int			i;
  int			err;

  err = 0;
  i = -1;
  while (req.getSize() > 0)
    if (sendToWorker(_worker[++i % _nbWorker], req.popFrontFd()) != 0)
      err = -1;
  return (err);
}
