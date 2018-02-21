//
// Worker.cpp for  in /home/albert_q/rendu/Tech3/Zia/cpp_zia/src/Network
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Tue Feb  6 11:03:49 2018 Quentin Albertone
// Last update Wed Feb 21 17:41:35 2018 Quentin Albertone
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

void			Worker::receivFd()
{
  unsigned char		*data;
  char			cBuffer[256];
  //int			fd;
  char			mBuffer[256];
  struct msghdr		msg;
  struct iovec		iov = {.iov_base = mBuffer, .iov_len = sizeof(mBuffer)};
  struct cmsghdr	*cmsg;

  msg.msg_iov = &iov;
  msg.msg_iovlen = 1;
  msg.msg_control = cBuffer;
  msg.msg_controllen = sizeof(cBuffer);

  if (recvmsg(_srvFd, &msg, 0) < 0)
    return ;

  cmsg = CMSG_FIRSTHDR(&msg);
  data = CMSG_DATA(cmsg);

  _cliFd = *((int *)data);
  dprintf(_logFd, "[%d:%d] - new client %d\n", _pid, _id, _cliFd);
}

void			Worker::handleRequestFromClient()
{
  std::vector<char>	buff(BUFFSIZE);
  int			bytes;

  dprintf(_logFd, "[%d:%d]:%d - Reading fd\n", _pid, _id, _cliFd);
  while ((bytes = recv(_cliFd, &buff[0], BUFFSIZE, 0)) == BUFFSIZE)
    {
      _cliReq.append(buff.cbegin(), buff.cend());
    }
  _cliReq.append(buff.cbegin(), buff.cend());
  dprintf(_logFd, "[%d:%d]:%d - %s\n", _pid, _id, _cliFd, _cliReq.c_str());
  resetClient();
}

void			Worker::resetClient()
{
  _cliFd = 0;
  _cliReq.erase(_cliReq.begin(), _cliReq.end());
}

void			Worker::loop()
{
  while (true)
    {
      receivFd();
      if (_cliFd > 0)
	handleRequestFromClient();
    }
}
