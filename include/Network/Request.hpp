//
// Request.hpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Nov  8 17:10:18 2017 Quentin Albertone
// Last update Wed Jan 24 12:56:58 2018 Quentin Albertone
//

#ifndef REQUEST_HPP_
# define REQUEST_HPP_

# include "ziainclude.hpp"
# include "Client.hpp"

class			RequestList
{
  RequestList();
  RequestList(RequestList const &);
  ~RequestList();
  RequestList					&operator=(RequestList &);

  void						setRequest(Client *, std::string);
  RequestList					&operator+(RequestList const &);

  std::vector<std::pair<Client *, std::string>>		getRequestList();
  void						displayRequest();

protected:
  std::vector<std::pair<Client *, std::string>>	_request;
};

//bool						operator<(RequestList const &Request, RequestList const &list);
#endif /* ! REQUEST_HPP_ */
