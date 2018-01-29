//
// Client.hpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Nov  8 14:18:49 2017 Quentin Albertone
// Last update Tue Jan 23 18:50:07 2018 Quentin Albertone
//

#ifndef CLIENT_HPP_
# define CLIENT_HPP_
# include "ziainclude.hpp"

class			Client
{
public:
  Client(int server);
  Client(Client const &client);
  ~Client();
  Client &operator=(Client const &client);

  int		getFd() const;
  t_sockaddr_in	const	*getSock();
  socklen_t 	getSize() const;
  t_pollfd	getPoll() const;

  // Optionnal
  std::string const	&getAddr();
  unsigned short	getPort() const;

  Client		&operator*();

protected:
  int			_fd;
  t_sockaddr_in		_sock;
  socklen_t		_size;
  t_pollfd		_poll;

  // Optionnal
  unsigned short	_port;
  std::string		_addr;
};
#endif /* CLIENT_HPP_ */
