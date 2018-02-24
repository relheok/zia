/* BEGIN TEST CODE */

# include <sys/un.h>
# include <sys/socket.h>

# include <unistd.h>
# include <stdio.h>

# include <string.h>

# include <netinet/in.h>

typedef struct sockaddr_in	t_sockaddr_in;
typedef	struct sockaddr_un	t_sockaddr_un;
typedef struct sockaddr		t_sockaddr;

// Inet Socket part
int			create_socket(int port)
{
  int			fd;
  t_sockaddr_in		addr;

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 3)
    {
      printf("Error socket: %d\n", fd);
      return (fd);
    }
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  if (bind(fd, (t_sockaddr *)&addr, sizeof(t_sockaddr_in)) < 0)
    {
      printf("Error bind\n");
      return (0);
    }
  if (listen(fd, 42))
    {
      printf("Error listen\n");
      return (-10);
    }
  return (fd);
}

int			accept_socket(int fd, int port)
{
  t_sockaddr_in		addr;
  int			fd_cli;
  int			addrlen;

  addrlen = sizeof(addr);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  if ((fd_cli = accept(fd, (t_sockaddr *)&addr, (socklen_t *)&addrlen)) == -1)
    printf("Error accept: %d\n", fd_cli);
  printf("New client fd: %d\n", fd_cli);
  return (fd_cli);
}
/* END TEST CODE */
