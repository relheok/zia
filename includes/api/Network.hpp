//
// Socket.hpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 14:41:38 2017 Quentin Albertone
// Last update Mon Nov  6 10:10:57 2017 Quentin Albertone
//

#ifndef SOCKET_H_
# define SOCKET_H_
# include "ziainclude.hpp"

namespace	Network
{
  class		Socket
  {
  public:
    Socket(int port);
    Socket(Socket const &socket);
    ~Socket();
    Socket		&operator=(Socket const &socket);

    int			getFd() const;
    int			getPort() const;
    t_sockaddr_in		*getSock();
    socklen_t		getSize() const;

  protected:
    int			_fd;
    int			_port;
    t_sockaddr_in		_sock;
    socklen_t		_size;
  };

  class		Server
  {
  public:
    Server();
    Server(int port);
    Server(Server const &server);
    ~Server();
    Server	operator=(Server const &server);

  protected:

  }
};

std::ostream	&operator<<(std::ostream &os, Network::Socket const &socket);

#endif /* !SOCKET_H_ */
