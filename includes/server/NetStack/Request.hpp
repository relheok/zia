//
// Request.hpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Nov  8 17:10:18 2017 Quentin Albertone
// Last update Sat Feb 24 00:25:44 2018 Quentin Albertone
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

  void						setRequest(Client *);
  std::list<Client *>				getRequestList();
  int						popFrontFd();
  int						getSize();

  RequestList					&operator>>(Client *);
  RequestList					&operator+(RequestList const &);
  //  void						displayRequest();

protected:
  std::list<Client *>				_request;
};

//bool						operator<(RequestList const &Request, RequestList const &list);
#endif /* ! REQUEST_HPP_ */
