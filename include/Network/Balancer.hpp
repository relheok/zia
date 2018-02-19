//
// Balancer.hpp for  in /home/albert_q/rendu/Tech3/Zia/cpp_zia/include/Network
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Wed Feb  7 14:26:37 2018 Quentin Albertone
// Last update Mon Feb 12 20:01:37 2018 Quentin Albertone
//

#ifndef BALANCER_HPP_
# define BALANCER_HPP_

# include "ziainclude.hpp"
# include "Worker.hpp"

class			Balancer
{
public:
  Balancer();
  ~Balancer();

  //void			send(RequestList &list);
  void			createSocket();
  int			createWorker();
  void			acceptWorker();
  void			display();

  void			sendWorker(char **argv);

protected:
  int			_fd;
  std::map<int, int>	_worker;
  int			_nbWorker;
};


#endif /* !BALANCER_HPP_ */
