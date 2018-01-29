//
// Request.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Nov  8 17:52:26 2017 Quentin Albertone
// Last update Wed Jan 24 13:26:22 2018 Quentin Albertone
//

//#include <utility>
#include "Request.hpp"

RequestList::RequestList()
{
  std::cout << "Create RequestList" << std::endl;
}

RequestList::RequestList(RequestList const &other)
  :_request(other._request)
{
}

RequestList::~RequestList()
{
  //delete _request;
}

RequestList		&RequestList::operator=(RequestList &req)
{
  if (this != &req)
    _request = req._request;
  return (*this);
}

// ------------------------------------------------------------------------------------------------ //

// RequestList				&RequestList::operator*()
// {
//   return (*this);
// }

void					RequestList::setRequest(Client *client, std::string query)
{
  _request.push_back(std::make_pair(client, query));
}

RequestList				&RequestList::operator+(RequestList const &list)
{
  _request.insert(_request.end(), list._request.begin(), list._request.end());
  return (*this);
}

std::vector<std::pair<Client *, std::string>>		RequestList::getRequestList()
{
  return (_request);
}

void					RequestList::displayRequest()
{
  std::vector<std::pair<Client *, std::string>>::iterator it = _request.begin();

  for(it; it != _request.end(); ++it)
    std::cout << "[" << it->first->getFd() << "]" << it->second << std::endl;
}
