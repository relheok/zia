//
// Worker.cpp for  in /home/albert_q/rendu/Tech3/Zia/cpp_zia/src/Network
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Tue Feb  6 11:03:49 2018 Quentin Albertone
// Last update Wed Feb 21 21:48:51 2018 Quentin Albertone
//

#include "Worker.hpp"

Worker::Worker(int id, zia::Daemon *daemon)
  : _id(id)
  , _daemon(daemon)
{
  _pid = getpid();
  _pPid = getppid();

  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Created begin 1");
  //zia::Daemon &daemon = zia::Daemon::getInstance();
  zia::api::ConfigManager *conf = _daemon->getConf();
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Created begin 2");
  zia::api::ModuleManager *manager = _daemon->getModuleManager();
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Created begin 3");
  conf->getConf();
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Created begin 4");
  manager->getModules();
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Created begin 5");

    // _http.reset(new zia::api::HttpInterpreter(conf->getConf(), std::map<std::string, std::string>{{"localhost", "."}}, manager->getModules()));
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Created begin 7");

  sleep(1);
  if ((_logFd = open(_DEBUG_FILE, O_CREAT | O_APPEND | O_RDWR, _RIGHT)) < 3)
    {
      zia::Logger::getInstance().error("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - " + "Error debug file");
      //std::cout << "[" << _pid << ":" << _id << "] - " << "Error debug file" << std::endl;
    }
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Created end");
  createSocketWorker();
  loop();
}

Worker::~Worker()
{
  //dprintf(_logFd, "[%d:%d] - Disconnect worker\n", _pid, _id);
  close(_srvFd);
  close(_logFd);
}

void			Worker::createSocketWorker()
{
  t_sockaddr_un		addr;

  if ((_srvFd = socket(AF_UNIX, SOCK_STREAM, 0)) < 3)
    {
      zia::Logger::getInstance().error("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Error create socket");
      //dprintf(_logFd, "[%d:%d] - Error create socket\n", _pid, _id);
      return ;
    }
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Create socket");
  //dprintf(_logFd, "[%d:%d] - Create socket\n", _pid, _id);
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, SRV_SOCK_PATH);
  if (connect(_srvFd, (t_sockaddr *)&addr, sizeof(t_sockaddr_un)) < 0)
    {
      zia::Logger::getInstance().error("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Error connect Socket");
      //dprintf(_logFd, "[%d:%d] - Error connect socket: %s\n", _pid, _id, SRV_SOCK_PATH);
      return ;
    }
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - Connect on" +
				  SRV_SOCK_PATH + std::to_string(_srvFd));
  //  dprintf(_logFd, "[%d:%d] - Connect on %s with fd: %d\n",
  //	  _pid, _id, SRV_SOCK_PATH, _srvFd);
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
  zia::Logger::getInstance().info("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "] - New client");
  //  dprintf(_logFd, "[%d:%d] - new client %d\n", _pid, _id, _cliFd);
}

void			Worker::handleRequestFromClient()
{
  std::vector<char>	buff(BUFFSIZE);
  int			bytes;

  //dprintf(_logFd, "[%d:%d]:%d - Reading fd\n", _pid, _id, _cliFd);
  while ((bytes = recv(_cliFd, &buff[0], BUFFSIZE, 0)) == BUFFSIZE)
    {
      _cliReq.append(buff.cbegin(), buff.cend());
    }
  _cliReq.append(buff.cbegin(), buff.cend());
  zia::Logger::getInstance().error("[" + std::to_string(_pid) + ":" + std::to_string(_id) + "]:" + std::to_string(_cliFd) +
				   "- " + _cliReq);
  //  dprintf(_logFd, "[%d:%d]:%d - %s\n", _pid, _id, _cliFd, _cliReq.c_str());
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
	  //resp = _http.get()->interpret(_cliReq);
	  //write(_cliFd, resp.c_str(), resp.size());
	  resetClient();
	}
    }
}
