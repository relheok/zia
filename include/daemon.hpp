//
// daemon.hpp for zia in /home/koehle_j/rendu/cpp/cpp_zia
//
// Made by Jérémy Koehler
// Login   <koehle_j@epitech.net>
//
// Started on  Tue Jan  9 10:06:13 2018 Jérémy Koehler
// Last update Fri Jan 19 15:22:31 2018 Jérémy Koehler
//

#ifndef DAEMON_HPP_
# define DAEMON_HPP_

# include <cstdlib>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <syslog.h>

# include <iostream>
# include <fstream>

namespace zia {
  class Daemon {

  public:
    static Daemon	&getInstance(std::string file = "/run/zia.pid");
    ~Daemon()					= default;

    void		stop();
    bool		isAlive();

    // signal handlers
    static void		shutdownSignal(int sig);
    static void		reloadSignal(int sig);

  private:
    Daemon(std::string file);
    static void		daemonize();
    static void		closeParent();
    static void		writePid();
    bool		killProcess(std::string fileName);

    bool	_killed;

  public:
    //avoid copies
    Daemon(Daemon const&)			= delete;
    void	operator=(Daemon const&)	= delete;
  };
}

#endif /* !DAEMON_HPP_ */
