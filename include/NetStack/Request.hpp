//
// Request.hpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Nov  8 17:10:18 2017 Quentin Albertone
// Last update Wed Feb 21 11:54:29 2018 Quentin Albertone
//

#ifndef REQUEST_HPP_
# define REQUEST_HPP_

# include "ziainclude.hpp"
# include "Client.hpp"

class			RequestList
{
public:
  RequestList();
  RequestList(RequestList const &);
  ~RequestList();
  RequestList					&operator=(RequestList &);

  void						setRequest(Client *, std::string);
  std::list<std::pair<Client *, std::string>>	getRequestList();
  int						popFrontFd();
  int						getSize();

  RequestList					&operator>>(std::pair<Client *, std::string>);
  RequestList					&operator+(RequestList const &);
  void						displayRequest();

protected:
  std::list<std::pair<Client *, std::string>>	_request;
};

//bool						operator<(RequestList const &Request, RequestList const &list);
#endif /* ! REQUEST_HPP_ */
