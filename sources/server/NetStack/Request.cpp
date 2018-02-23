//
// Request.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Nov  8 17:52:26 2017 Quentin Albertone
// Last update Sat Feb 24 00:25:13 2018 Quentin Albertone
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

void					RequestList::setRequest(Client *client)
{
  _request.push_back(client);
}

RequestList				&RequestList::operator+(RequestList const &list)
{
  _request.insert(_request.end(), list._request.begin(), list._request.end());
  return (*this);
}

int					RequestList::getSize()
{
  return (_request.size());
}

int					RequestList::popFrontFd()
{
  int					fd;

  if (_request.size() < 1)
    {
      zia::Logger::getInstance().error("[REQUESTSTACK] - invalide size of list");
      return (-1);
    }
  fd = _request.front()->getFd();
  _request.pop_front();
  return (fd);
}

std::list<Client *>		RequestList::getRequestList()
{
  return (_request);
}

// void					RequestList::displayRequest()
// {
//   std::list<Client *>::iterator it = _request.begin();

//   std::cout << "RequestList: " << std::endl;
//   for(; it != _request.end(); ++it)
//     zia::Logger::getInstance().debug("[REQUESTSTACK] - request from client: " + std::to_string(*it->first->getFd()));
//   //std::cout << "[" << it->first->getFd() << "] " << it->second;
// }
