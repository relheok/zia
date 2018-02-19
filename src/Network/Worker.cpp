//
// Worker.cpp for  in /home/albert_q/rendu/Tech3/Zia/cpp_zia/src/Network
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Tue Feb  6 11:03:49 2018 Quentin Albertone
// Last update Mon Feb 12 16:12:50 2018 Quentin Albertone
//

#include "Worker.hpp"

Worker::Worker(int id)
  : _id(id)
{
  sleep(1);
  _pid = getpid();
  _pPid = getppid();
  if ((_logFd = open(_DEBUG_FILE, O_CREAT | O_APPEND | O_RDWR, _RIGHT)) < 3)
    std::cout << "[" << _pid << ":" << _id << "] - " << "Error debug file" << std::endl;
  dprintf(_logFd, "[%d:%d] - Created\n", _pid, _id);
  createSocketWorker();
  loop();
}

Worker::~Worker()
{
  dprintf(_logFd, "[%d:%d] - Disconnect worker\n", _pid, _id);
  close(_srvFd);
  close(_logFd);
}

void			Worker::createSocketWorker()
{
  t_sockaddr_un		addr;

  if ((_srvFd = socket(AF_UNIX, SOCK_STREAM, 0)) < 3)
    {
      dprintf(_logFd, "[%d:%d] - Error create socket\n", _pid, _id);
      return ;
    }
  dprintf(_logFd, "[%d:%d] - Create socket\n", _pid, _id);
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, SRV_SOCK_PATH);
  if (connect(_srvFd, (t_sockaddr *)&addr, sizeof(t_sockaddr_un)) < 0)
    {
      dprintf(_logFd, "[%d:%d] - Error connect socket: %s\n", _pid, _id, SRV_SOCK_PATH);
      return ;
    }
  dprintf(_logFd, "[%d:%d] - Connect on %s with fd: %d\n",
	  _pid, _id, SRV_SOCK_PATH, _srvFd);
}

// void			Worker::getClientFd(char *buff)
// {
//   int			sourceFd;
//   char			file[64];

//   sourceFd = atoi(buff);
//   asprintf(&file)
// }

void			Worker::loop()
{
  ssize_t		bytes;
  char			buff[BUFFSIZE];

  memset(buff, 0, BUFFSIZE);
  while ((bytes = read(_srvFd, &buff, BUFFSIZE)) > 0)
    {
      dprintf(_logFd, "[%d:%d] - %s\n", _pid, _id, buff);
      memset(buff, 0, BUFFSIZE);
    }
}
