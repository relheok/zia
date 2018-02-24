//
// Worker.cpp for  in /home/albert_q/rendu/Tech3/Zia/cpp_zia/src/Network
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Tue Feb  6 11:03:49 2018 Quentin Albertone
// Last update Sat Feb 24 17:14:47 2018 Jérémy Koehler
//

#include "Worker.hpp"

Worker::Worker(int id, zia::Daemon *daemon)
  : _id(id)
  , _daemon(daemon)
{
  _pid = getpid();
  _pPid = getppid();

  zia::api::ConfigManager *conf = _daemon->getConf();
  zia::api::ModuleManager *manager = _daemon->getModuleManager();
  conf->getConf();
  manager->getModules();

  _http.reset(new zia::api::HttpInterpreter(conf->getConf(), std::map<std::string, std::string>{{"localhost", "."}}, manager->getModules()));

  sleep(1);
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Created end");

  createSocketWorker();
  loop();
}

Worker::~Worker()
{
  zia::Logger::getInstance().warning("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Worker is stopping his activity");
  close(_srvFd);
}

void			Worker::createSocketWorker()
{
  t_sockaddr_un		addr;

  if ((_srvFd = socket(AF_UNIX, SOCK_STREAM, 0)) < 3)
    {
      zia::Logger::getInstance().error("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Error create socket");
      return ;
    }
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Create socket");
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, SRV_SOCK_PATH);

  if (connect(_srvFd, (t_sockaddr *)&addr, sizeof(t_sockaddr_un)) < 0)
    {
      zia::Logger::getInstance().error("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Error connect Socket");
        return ;
    }
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Connect on " +
				  SRV_SOCK_PATH + std::to_string(_srvFd));
}

void			Worker::receivFd()
{
  unsigned char		*data;
  char			cBuffer[256];
  char			mBuffer[256];
  char			nBuffer[256];
  struct msghdr		msg;
  struct iovec		iov = {.iov_base = mBuffer, .iov_len = sizeof(mBuffer)};
  struct cmsghdr	*cmsg;

  msg.msg_iov = &iov;
  msg.msg_iovlen = 1;
  msg.msg_name = nBuffer;
  msg.msg_namelen = sizeof(nBuffer);
  msg.msg_control = cBuffer;
  msg.msg_controllen = sizeof(cBuffer);

  zia::Logger::getInstance().info("[WORKER] waiting for fd");
  if (recvmsg(_srvFd, &msg, 0) < 0)
    {
      zia::Logger::getInstance().error("[WORKER] failed to receive fd");
      return ;
    }
  zia::Logger::getInstance().info("[WORKER] fd received");

  cmsg = CMSG_FIRSTHDR(&msg);
  data = CMSG_DATA(cmsg);

  _cliFd = *((int *)data);
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - New client " + std::to_string(_cliFd));
}

void			Worker::handleRequestFromClient()
{
  std::vector<char>	buff(BUFFSIZE);
  int			bytes;

  while ((bytes = recv(_cliFd, &buff[0], BUFFSIZE, 0)) == BUFFSIZE)
    _cliReq.append(buff.cbegin(), buff.cend());
  _cliReq.append(buff.cbegin(), buff.cend());
  zia::Logger::getInstance().error("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "]:" + std::to_string(_cliFd) +
				   "- " + _cliReq);
}

void			Worker::resetClient()
{
  _cliFd = 0;
  _cliReq.erase(_cliReq.begin(), _cliReq.end());
}

void			Worker::loop()
{
  std::string		resp;

  while (true)
    {
      receivFd();
      if (_cliFd > 0)
      	{
      	  handleRequestFromClient();

      	  resp = _http.get()->interpret(_cliReq);
	        // resp = std::string("received : ") + _cliReq;

	  if (send(_cliFd, resp.c_str(), resp.size(), 0) < 0)
	    zia::Logger::getInstance().error("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "]:"
	  				     + std::to_string(_cliFd) + " - Can't send answer to client");
      	  resetClient();
      	}
    }
}
