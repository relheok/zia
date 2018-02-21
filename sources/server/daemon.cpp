//
// daemon.cpp for zia in /home/koehle_j/rendu/cpp/cpp_zia
//
// Made by Jérémy Koehler
// Login   <koehle_j@epitech.net>
//
// Started on  Tue Jan  9 10:04:17 2018 Jérémy Koehler
// Last update Wed Feb 21 19:39:58 2018 Quentin Albertone
//

#include "daemon.hpp"

zia::Daemon		&zia::Daemon::getInstance(std::string file) {
  static zia::Daemon	daemon(file);

  return daemon;
}

void	zia::Daemon::sendSignal(std::string signal)
{
  if (signal == "stop" || signal == "STOP"
      || signal == "quit" || signal == "QUIT")
    {
      if (killProcess(SIGINT) == false)
	std::cerr << "Failed to kill process" << std::endl;
    }
  else if (signal == "reload" || signal == "RELOAD")
    {
      if (killProcess(SIGUSR1) == false)
	std::cerr << "Failed to reload conf" << std::endl;
    }
  else
    {
      std::cerr << "Invalid signal " << signal << std::endl;
    }
}

void	zia::Daemon::stop() {
  remove(_fileName.c_str());
  _killed = false;
  Logger::getInstance().info("[ZIA] shutting down");
}

bool	zia::Daemon::isAlive() {
  return _killed;
}

void	zia::Daemon::setConf(api::ConfigManager *conf) {
  _conf = conf;
}

zia::api::ConfigManager  *zia::Daemon::getConf() {
  return _conf;
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

  struct stat info;
  if (stat(_fileName.c_str(), &info) != 0)
    {
      std::ofstream test(_fileName);

      if (!test.is_open()) {
	std::cerr << "Can not open file " << file << ": Permission denied" << std::endl;
	exit(2);
      };
      daemonize();
    }
  else
    {
      std::cerr << "Can not launch server: " << _fileName << " already exist." << std::endl;
      exit(2);
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
  Logger::getInstance().info("[ZIA] starting server");
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

bool		zia::Daemon::killProcess(int signal) {
  pid_t		pid;
  std::ifstream	file;

  file.open("/run/zia.pid");
  if (file.is_open()) {
    file >> pid;
    file.close();
    kill(pid, signal);
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
  zia::Logger::getInstance().info("[ZIA] reload conf");
}
