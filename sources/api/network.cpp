//
// socket.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 14:46:06 2017 Quentin Albertone
// Last update Sun Nov  5 16:57:17 2017 Quentin Albertone
//

#include "Socket.hpp"

Socket::Socket(int port)
  : _port(port)
{
  _sock.sin_family = AF_INET;
  _sock.sin_port = htons(_port);
  _sock.sin_addr.s_addr = INADDR_ANY;
  _size = sizeof(sockaddr_in);

  // Open socket and get fd on it
  if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) < 3)
    std::cout << "Error while create socket on port :" << _port << std::endl;
  std::cout << "Socket create on port : " << _port << std::endl;

  // Bind socket on ip and port / wait a t_sockaddr *
  if (bind(_fd, (const t_sockaddr *)&_sock, _size) == -1)
    std::cout << "\tError while binding socket" << std::endl;
  std::cout << "\tSocket bind" << std::endl;

  // Listen create a queue implicitely create maw client server can have
  if (listen(_fd, 42) == -1)
    std::cout << "\tError while listening on socket" << std::endl;
  std::cout << "\tSocket listening new client" << std::endl;
}

Socket::Socket(Socket const &socket)
  : _fd(socket._fd)
  , _port(socket._port)
  , _sock(socket._sock)
  , _size(socket._size)
{
}

Socket::~Socket()
{
  std::cout << "Close socket: " << _fd << " on port: " << _port << std::endl;
  close(_fd);
}

Socket		&Socket::operator=(Socket const &other)
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

std::ostream	&operator<<(std::ostream &os, Socket const &socket)
{
  os << "Socket: " << socket.getFd() << " port: " << socket.getPort();
  return (os);
}


// ---------------------------- ----------------------------  //
//		Coplien Form and minimal function	      //
// ---------------------------- ----------------------------  //

int		Socket::getFd() const
{
  return (_fd);
}

int		Socket::getPort() const
{
  return (_port);
}

t_sockaddr_in	*Socket::getSock()
{
  return (&_sock);
}

socklen_t	Socket::getSize() const
{
  return (_size);
}
