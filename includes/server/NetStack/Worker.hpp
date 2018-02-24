//
// Worker.hpp for  in /home/albert_q/rendu/Tech3/Zia/cpp_zia/include/Network
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Tue Feb  6 11:03:59 2018 Quentin Albertone
// Last update Sat Feb 24 01:36:57 2018 Quentin Albertone
//

#ifndef WORKER_HPP_
# define WORKER_HPP_
# include "ziainclude.hpp"
# include "http/HttpInterpreter.hpp"
# include "daemon.hpp"
# include "logger.hpp"


# ifndef __STREAMPROTO_
#  define __STREAMPROTO_

#  include <sys/un.h>
#  include <sys/socket.h>
#  include <unistd.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <fcntl.h>

#  include <sys/stat.h>
#  include <sys/time.h>

#  include <sys/wait.h>

#  define SRV_SOCK_PATH		"/tmp/ux_socket"
#  define BUFFSIZE		1024
#  define SRV_BACKLOG		100

#  define _DEBUG_FILE		"/tmp/_debug"
#  define _DEBUG_NBWORKER	2

#  define _RIGHT		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP

typedef struct sockaddr_un	t_sockaddr_un;
typedef struct sockaddr		t_sockaddr;

# endif /* !__STREAMPROTO_ */

# define _BEGINMSG		"[" << _pid << ":" << _id << "] - "

class			Worker
{
public:
  Worker(int id, zia::Daemon *);
  ~Worker();

  void			receivFd();
  void			handleRequestFromClient();
  void			resetClient();

  void			createSocketWorker();
  void			loop();
  //  void			sendToClient(std::string &);

protected:
  int			_id;
  int			_srvFd;
  int			_logFd;

  int			_cliFd;
  std::string		_cliReq;

  int			_pid;
  int			_pPid;

  zia::Daemon		*_daemon;
  std::unique_ptr<zia::api::HttpInterpreter> _http{nullptr};
};


#endif /* !WORKER_HPP_ */
