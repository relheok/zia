//
// Request.hpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Nov  8 17:10:18 2017 Quentin Albertone
// Last update Tue Feb 20 12:14:14 2018 Jérémy Koehler
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

  RequestList					&operator>>(std::pair<Client *, std::string>);
  RequestList					&operator+(RequestList const &);
  void						displayRequest();

protected:
  std::list<std::pair<Client *, std::string>>	_request;
};

//bool						operator<(RequestList const &Request, RequestList const &list);
#endif /* ! REQUEST_HPP_ */
