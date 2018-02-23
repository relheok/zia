//
// Socket.hpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 14:41:38 2017 Quentin Albertone
// Last update Sat Feb 24 00:26:14 2018 Quentin Albertone
//

#ifndef NETWORK_HPP_
# define NETWORK_HPP_

# include "ziainclude.hpp"
# include "Client.hpp"
# include "Request.hpp"
# include "Balancer.hpp"

namespace	Network
{
  class		Socket
  {
  public:
    Socket(int port);
    Socket(Socket const &socket);
    ~Socket();
    Socket		&operator=(Socket const &socket);

    // Socket
    int				getFd() const;
    int				getPort() const;
    t_sockaddr_in		*getSock();
    socklen_t			getSize() const;
    RequestList			&getRequest();
    // Client
    std::vector<t_pollfd>	getClientFds();

    void			loop();

    // void			displayRequest();

  private:
    int				_fd;
    int				_port;
    t_sockaddr_in		_sock;
    socklen_t			_size;

    t_pollfd			_pollServer;

    RequestList			_req;
    std::vector<t_pollfd>	_clientFds;
    std::map<int, Client *>	_clients;
  };

  class		NetStack
  {
  public:
    NetStack();
    NetStack(int port);
    NetStack(NetStack const &server);
    ~NetStack();
    NetStack			operator=(NetStack const &server);

    //NetStack			&operator<<(int port);
    //NetStack			&operator<<(Socket &s);
  private:
    std::vector<Socket *>	_socket;

  };
};

std::ostream	&operator<<(std::ostream &os, Network::Socket const &socket);

#endif /* !NETWORK_H_ */
