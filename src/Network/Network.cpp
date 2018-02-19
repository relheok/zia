//
// socket.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 14:46:06 2017 Quentin Albertone
// Last update Mon Feb 12 17:54:51 2018 Quentin Albertone
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
    std::cout << "[:" << _port << "] - Error while create socket on port :" << _port << std::endl;
  std::cout << "[:" << _port << "] - Socket create on port : " << _port << std::endl;


  // Bind socket on ip and port / wait a t_sockaddr *
  if (bind(_fd, (const t_sockaddr *)&_sock, _size) == -1)
    std::cout << "\t[:" << _port << "] - Error while binding socket" << std::endl;
  std::cout << "\t[:" << _port << "] - Socket bind" << std::endl;

  // Listen create a queue implicitely create maw client server can have
  if (listen(_fd, 42) == -1)
    std::cout << "\t[:" << _port << "] - Error while listening on socket" << std::endl;

  std::cout << "\t[:" << _port << "] - Add POLLIN event." << std::endl;
  std::cout << "[:" << _port << "] - Socket listening new client" << std::endl;
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
  std::cout << "[:" << _port << "] - Close socket: " << _fd << " on port: " << _port << std::endl;
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

// ---------------------------- ----------------------------  //
//		manage clients functions		      //
// ---------------------------- ----------------------------  //

void			Network::Socket::loop()
{
  int			check;

  // Check the socket server and accept new client
  _pollServer.fd = _fd;
  _pollServer.events = POLLIN;

  if ((check = poll(&_pollServer, 1, 2000)) == -1)
    std::cout << "[:" << _port << "] - Erreur poll serverSocket" << std::endl;
  std::cout << "[" << _port << "] - loop - poll: " << check << std::endl;
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

      // // Debug //
      // for (std::map<int, Client *>::iterator i = _clients.begin, i != )

      if ((check = poll(_clientFds.data(), static_cast<nfds_t>(_clientFds.size()), 10)) == -1)
	std::cout << "\t[:" << _port << "] - Erreur poll client on socket: " << _fd << std::endl;
      if (check > 0)
	{
	  // for (std::vector<t_pollfd>::iterator it = _clientFds.begin(); it != _clientFds.end(); it++)
	  std::vector<t_pollfd>::iterator it = _clientFds.begin();
	  while (it != _clientFds.end())
	    {
	      // Check if client exist
	      if ((clientIt = _clients.find(it->fd)) == _clients.end())
		{
		  it = _clientFds.erase(it);
		  std::cout << "\t[:" << _port << "] - deleted !" << std::endl;
		}
	      //	      Client const &client = (*clientIt->second);
	      disconnect = false;

	      // Check error from connection with client
	      if (it->revents & (POLLERR | POLLHUP | POLLNVAL))
		{
		  std::cout << "\t[:" << _port << "] - Erreur in connection of client: " << it->fd << std::endl;
		  disconnect = true;
		}
	      else if (it->revents & POLLIN)
		{
		  char		rec[200] = {0};

		  		  std::cout << "\t[:" << _port << "] - New input from: " << clientIt->first << std::endl;
		  if (read(clientIt->first, &rec, 199) == -1 || rec[0] == 0)
		    disconnect = true;
		  // Register new POLLIN
		  _req.setRequest(clientIt->second, std::string(rec)/*"NULL"*/);
		}
	      // Disconnect user with matters
	      if (disconnect)
		{
		  std::cout << "\t[:" << _port << "] - Disconnecting user: " << clientIt->first << std::endl;
		  it = _clientFds.erase(it);
		  clientIt = _clients.erase(clientIt);
		}
	      else
		++it;
	    }
	}
    }
}

void			Network::Socket::displayRequest()
{
  _req.displayRequest();
}
