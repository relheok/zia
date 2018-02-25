//
// main.cpp for  in /home/albert_q/rendu/test/cpp/Socket
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Sun Nov  5 16:42:43 2017 Quentin Albertone
// Last update Sun Feb 25 02:13:21 2018 Jérémy Koehler
//

#include "main.hpp"
#include "logger.hpp"

#include <getopt.h>
#include "daemon.hpp"
#include "http/HttpInterpreter.hpp"
#include "module_manager/ModuleManager.hpp"
#include "Network.hpp"

void		usage(std::string execName)
{
  std::cout << "Usage: " << execName << " [OPTION]" << std::endl;
  std::cout << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -c, --config=file   set configuration file (default: /etc/zia/zia.json)" << std::endl;
  std::cout << "  -r, --reload        reload the configuration file" << std::endl;
  std::cout << "  -s, --signal=sig    send signal sig to the master process:" << std::endl;
  std::cout << "                        stop, quit, restart, reload" << std::endl;
  std::cout << "  -h, --help          display this help and exit" << std::endl;
}

int		process(std::string confPath)
{
  try {
    std::cout << "Run with config file: " << confPath << std::endl;
    // zia::api::ConfigManager p(confPath);
    std::unique_ptr<zia::api::ConfigManager> p(new zia::api::ConfigManager(confPath));
    std::unique_ptr<zia::api::ModuleManager> m(new zia::api::ModuleManager);
    zia::Daemon &daemon = zia::Daemon::getInstance();

    if (!p.get()->browser_conf())
      zia::Logger::getInstance().error("No conf file");
    std::map<std::string, std::string> map = p.get()->getRoots();
    m.get()->init(p.get()->getListModules(), p.get()->getConf());

    size_t port = 4242;
    try {
      port = static_cast<size_t>(std::get<long long>(p.get()->getConf()["port"].v));
    } catch (std::exception &) {
      zia::Logger::getInstance().error("No port ! Default : 4242");
    }
    Network::Socket	inet(port);

    // pipe.display();

    daemon.setConf(p.get());
    daemon.setModuleManager(m.get());

    Balancer		pipe;

    while (daemon.isAlive()) {
      inet.loop();
      pipe.balancer(inet.getRequest());
      sleep(3);
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return (1);
  }
  return (0);
}

int		main(int argc, char **argv)
{
  static struct option long_options[] =
    {
      {"config", required_argument, 0, 'c'},
      {"reload", no_argument, 0, 'r'},
      {"signal", required_argument, 0, 's'},
      {"help", no_argument, 0, 'h'}
    };
  int option_index = 0;
  int c;
  std::string confPath("./example/example.json"); // this will be the default value of our conf path

  while ((c = getopt_long (argc, argv, "c:rs:h",
			   long_options, &option_index)) != -1)
    {
      switch (c)
	{
	case 'c':
	  confPath = optarg;
	  break;
	case 'r':
	  zia::Daemon::sendSignal("reload");
	  return (0);
	case 's':
	  zia::Daemon::sendSignal(optarg);
	  if (std::string(optarg) != "restart")
	    return (0);
	  break;
	case 'h':
	  usage(argv[0]);
	  return (0);
	}
    }

  return (process(confPath));

  // backlog
  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

  return (0);
}

int		create_socket(int port);
int		accept_socket(int fd, int port);

int		old_main(int ac, char **av)
{
  int fd_cliGlobal;
  int fd_inetGlobal;
  try {
    std::string path((ac >= 2) ? (av[1]) : (""));
    zia::api::ConfigManager p(path);
    if (!p.browser_conf())
      std::cerr << "no conf file !" << std::endl;
    std::unique_ptr<zia::api::ModuleManager> m(new zia::api::ModuleManager);
    m.get()->init(p.getListModules(), p.getConf());

    /* BEGIN TEST CODE */
    char			buff[BUFFSIZE];
    zia::api::HttpInterpreter interpreter(p.getConf(), p.getRoots(), m.get()->getModules());

    printf("port: %d\n", std::stoi(av[2]));

    fd_inetGlobal = create_socket(std::stoi(av[2]));
    fd_cliGlobal = accept_socket(fd_inetGlobal, std::stoi(av[2]));
    memset(buff, 0, BUFFSIZE);
    while (read(fd_cliGlobal, &buff, BUFFSIZE) > 0)
      {
        try {
          std::cout << "\ngot :\n" << buff << '\n';
          std::string str = interpreter.interpret(buff);
          std::cout << "\nwrite :\n" << str << '\n';
          write(fd_cliGlobal, str.c_str(), str.size());
        } catch (std::exception &e) {
          std::cout << e.what() << '\n';
        }
        //printf("%s", buff);
        memset(buff, 0, BUFFSIZE);
      }
    close(fd_cliGlobal);
    close(fd_inetGlobal);
    /* END TEST CODE */

    //start server
    // while (daemon.isAlive()) {
    //   /*
    //   ** TODO
    //   */
    // }

    return (0);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return (-1);
  }
  return (0);
}
