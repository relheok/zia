//
// socket.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 14:46:06 2017 Quentin Albertone
// Last update Sat Feb 24 00:25:21 2018 Quentin Albertone
//

#include "Network.hpp"
//#include "Request.hpp"

// ---------------------------- ----------------------------  //
//			Coplien form			      //
// ---------------------------- ----------------------------  //

Network::Socket::Socket(int port)
  : _port(port)
{
  int		use;

  _sock.sin_family = AF_INET;
  _sock.sin_port = htons(_port);
  _sock.sin_addr.s_addr = INADDR_ANY;
  _size = sizeof(sockaddr_in);

  // Open socket and get fd on it
  if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) < 3 || (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &use, sizeof(use))) == -1)
    zia::Logger::getInstance().error("[Balancer] - Error while creating socket");
  zia::Logger::getInstance().info("[Balancer] - Socket create on port: " + std::to_string(_port));

  // Bind socket on ip and port / wait a t_sockaddr *
  if (bind(_fd, (const t_sockaddr *)&_sock, _size) == -1)
    zia::Logger::getInstance().error("[Balancer] - Error while bind socket");
  zia::Logger::getInstance().info("[Balancer] - Socket bind" + std::to_string(_port));

  // Listen create a queue implicitely create maw client server can have
  if (listen(_fd, 42) == -1)
    zia::Logger::getInstance().error("[Balancer] - Error while listening on socket");
  zia::Logger::getInstance().info("[Balancer] - Socket create whith success" + std::to_string(_port));
}

Network::Socket::Socket(Network::Socket const &socket)
  : _fd(socket._fd)
  , _port(socket._port)
  , _sock(socket._sock)
  , _size(socket._size)
{
}

Network::Socket::~Socket()
{
  zia::Logger::getInstance().warning("[Balancer] - Close MasterSocket: END OF NETWORKSTACK");
  close(_fd);
}

Network::Socket		&Network::Socket::operator=(Network::Socket const &other)
{
  if (&other != this)
    {
      _fd = other._fd;
      _port = other._port;
      _sock = other._sock;
      _size = other._size;
    }
  return (*this);
}

std::ostream	&operator<<(std::ostream &os, Network::Socket const &socket)
{
  os << "Socket: " << socket.getFd() << " port: " << socket.getPort();
  return (os);
}

// ---------------------------- ----------------------------  //
//		Getteur and Setteur function		      //
// ---------------------------- ----------------------------  //

int			Network::Socket::getFd() const
{
  return (_fd);
}

int			Network::Socket::getPort() const
{
  return (_port);
}

t_sockaddr_in		*Network::Socket::getSock()
{
  return (&_sock);
}

socklen_t		Network::Socket::getSize() const
{
  return (_size);
}

std::vector<t_pollfd>	Network::Socket::getClientFds()
{
  return (_clientFds);
}

RequestList		&Network::Socket::getRequest()
{
  return (_req);
}

// ---------------------------- ----------------------------  //
//		manage clients functions		      //
// ---------------------------- ----------------------------  //

void			Network::Socket::loop()
{
  int			check;

  // Check the socket server and accept new client
  _pollServer.fd = _fd;
  _pollServer.events = POLLIN;

  if ((check = poll(&_pollServer, 1, 100)) == -1)
    zia::Logger::getInstance().error("[Balancer] - Error Poll: MasterSocket");
  zia::Logger::getInstance().debug("[Balancer] - Loop poll");
  if (check > 0)
    {
      Client		*nClient = new Client(_fd);
      _clients.insert(std::pair<int, Client *>(nClient->getFd(), nClient));
      _clientFds.push_back(nClient->getPoll());
    }

  // Check input
  if (!_clients.empty())
    {
      bool				disconnect;

      std::map<int, Client *>::iterator	clientIt;

      if ((check = poll(_clientFds.data(), static_cast<nfds_t>(_clientFds.size()), 10)) == -1)
	zia::Logger::getInstance().error("[Balancer] - Error poll on client socket");
      if (check > 0)
	{
	  std::vector<t_pollfd>::iterator it = _clientFds.begin();
	  while (it != _clientFds.end())
	    {
	      // Check if client exist
	      if ((clientIt = _clients.find(it->fd)) == _clients.end())
		{
		  it = _clientFds.erase(it);
		  zia::Logger::getInstance().debug("[Balancer] - Delete client");
		}
	      disconnect = false;
	      // Check error from connection with client
	      if (it->revents & (POLLERR | POLLHUP | POLLNVAL))
		{
		  zia::Logger::getInstance().debug("[Balancer] - No client connection");
		  disconnect = true;
		}
	      else if (it->revents & POLLIN)
		{
		  zia::Logger::getInstance().info("[Balancer] - New input from : " + std::to_string(clientIt->first));
		  _req.setRequest(clientIt->second);
		  // TODO:
		  it->revents = 0;
		}
	      // Disconnect user with matters
	      if (disconnect)
		{
		  zia::Logger::getInstance().info("[Balancer] - Delete user : " + std::to_string(clientIt->first));
		  it = _clientFds.erase(it);
		  clientIt = _clients.erase(clientIt);
		}
	      else
		++it;
	    }
	}
    }
}

// void			Network::Socket::displayRequest()
// {
//   _req.displayRequest();
// }
