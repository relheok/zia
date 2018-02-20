//
// daemon.cpp for zia in /home/koehle_j/rendu/cpp/cpp_zia
//
// Made by Jérémy Koehler
// Login   <koehle_j@epitech.net>
//
// Started on  Tue Jan  9 10:04:17 2018 Jérémy Koehler
// Last update Tue Feb 20 17:01:27 2018 Jérémy Koehler
//

#include "daemon.hpp"

zia::Daemon		&zia::Daemon::getInstance(std::string file) {
  static zia::Daemon	daemon(file);

  return daemon;
}

void	zia::Daemon::stop() {
  remove(_fileName.c_str());
  _killed = false;
}

bool	zia::Daemon::isAlive() {
  return _killed;
}

void	zia::Daemon::setConf(api::ConfigManager *conf) {
  _conf = conf;
}

void	zia::Daemon::updateConf() {
  if (_conf)
    _conf->browser_conf();
}

zia::Daemon::Daemon(std::string file):
  _killed(true), _fileName(file), _conf(NULL) {
  signal(SIGCHLD, SIG_IGN);

  /* shutdown signals */
  signal(SIGTERM, zia::Daemon::shutdownSignal);
  signal(SIGINT, zia::Daemon::shutdownSignal);
  signal(SIGQUIT, zia::Daemon::shutdownSignal);
  signal(SIGKILL, zia::Daemon::shutdownSignal);

  /* As the other daemons: reload config file */
  signal(SIGHUP, zia::Daemon::shutdownSignal);

  /* do smth */
  signal(SIGUSR1, zia::Daemon::reloadSignal);
  signal(SIGUSR2, zia::Daemon::reloadSignal);

  if (!killProcess(file)) {
    std::ofstream test(file);

    if (!test.is_open()) {
      std::cerr << "Can not open file " << file << ": Permission denied" << std::endl;
      exit(2);
    }
    test.close();
    daemonize();
  }
}

void	zia::Daemon::daemonize() {
  /* Fork off the parent process */
  zia::Daemon::closeParent();
  writePid();

  /* Set new file permissions */
  // umask(0);

  /* Change the working directory to the appropriated directory */
  // chdir("/");

  /* Close all open file descriptors */
  for (int x = sysconf(_SC_OPEN_MAX); x >= 0; --x)
    close (x);
}

void	zia::Daemon::closeParent() {
  pid_t	pid = fork();

  if (pid < 0)
    std::exit(EXIT_FAILURE);
  else if (pid > 0)
    std::exit(EXIT_SUCCESS);
  /* On success: The child process becomes session leader */
  if (setsid() < 0)
    std::exit(EXIT_FAILURE);
}

void		zia::Daemon::writePid() {
  std::ofstream	file;

  file.open("/run/zia.pid");
  file << getpid() << std::endl;
  file.close();
}

bool		zia::Daemon::killProcess(std::string fileName) {
  pid_t		pid;
  std::ifstream	file;

  file.open(fileName);
  if (file.is_open()) {
    _killed = false;
    file >> pid;
    file.close();
    kill(pid, SIGINT);
    return true;
  }
  return false;
}

// signal handlers
void	zia::Daemon::shutdownSignal(__attribute__((unused))int sig) {
  zia::Daemon::getInstance().stop();
}

void	zia::Daemon::reloadSignal(__attribute__((unused))int sig) {
  zia::Daemon::getInstance().updateConf();
}
