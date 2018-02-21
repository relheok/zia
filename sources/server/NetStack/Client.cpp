//
// Client.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Nov  8 14:54:28 2017 Quentin Albertone
// Last update Tue Jan 23 18:51:12 2018 Quentin Albertone
//

#include "Client.hpp"

Client::Client(int server)
{
  std::cout << "Acccepting new client" << std::endl;
  _size = sizeof(_sock);
  if ((_fd = accept(server, (t_sockaddr *)(&_sock), &_size)) < 3)
    std::cout << "\tError while accepting client" << std::endl;
  //  _addr = Sockets::GetAddress(_sock);
  _port = ntohs(_sock.sin_port);

  // Manage poll events POLLIN
  _poll.fd = _fd;
  _poll.events = POLLIN;

  std::cout << "Accepting new client and add poll event" << std::endl;
  std::cout << "\tNew client: " << _fd << " addr: " << _addr << ":" << _port << std::endl;
}

Client::Client(Client const &client)
  : _fd(client._fd)
  , _sock(client._sock)
  , _size(client._size)
  , _port(client._port)
  , _addr(client._addr)
{
}

Client		&Client::operator=(Client const &client)
{
  if (this != &client)
    {
      _fd = client._fd;
      _sock = client._sock;
      _size = client._size;
      _port = client._port;
      _addr = client._addr;
    }
  return (*this);
}

Client::~Client()
{
  std::cout << "Dtor client: " << _fd << std::endl;
}


// --------------------------------------------------------------------------------------------- //

Client				&Client::operator*()
{
  return (*this);
}

int			Client::getFd() const
{
  return (_fd);
}

t_sockaddr_in const	*Client::getSock()
{
  return (&_sock);
}

socklen_t		Client::getSize() const
{
  return (_size);
}

t_pollfd			Client::getPoll() const
{
  return (_poll);
}

std::string const	&Client::getAddr()
{
  return (_addr);
}

unsigned short		Client::getPort() const
{
  return (_port);
}
