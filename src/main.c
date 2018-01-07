/*
** main.c for  in /home/hazer/PSU_2016_myftp/src
**
** Made by hazer
** Login   <hazer@epitech.net>
**
** Started on  Tue May  9 16:08:28 2017 hazer
** Last update Thu May 18 12:12:24 2017 rezard
*/

#include <myftp.h>
#include <error.h>

int	listenServer(int fd)
{
  if (listen(fd, LIMITED_CLIENT) == FTP_ERR)
    {
      if (close(fd) == FTP_ERR)
	return (FTP_ERR);
      return (FTP_ERR);
    }
  return (FTP_OK);
}

int	acceptServer(int fd)
{
  struct sockaddr_in	si_client;
  socklen_t		si_size;
  t_client		client;
  int			pid;

  si_size = sizeof(si_client);
  while (1)
    {
      if ((client.fd = accept(fd, (struct sockaddr *)&si_client, &si_size))
	  == FTP_ERR)
	{
	  if (close(fd) == FTP_ERR)
	    return (FTP_ERR);
	  return (FTP_ERR);
	}
      client.ip = inet_ntoa(si_client.sin_addr);
      if ((pid = fork()) == 0)
	{
	  handleClient(&client);
	}
      else
	if (close(client.fd) == FTP_ERR)
	  return (FTP_ERR);
    }
  return (FTP_OK);
}

int	createServer(int port)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd;

  if (!(pe = getprotobyname("TCP")))
    return (FTP_ERR);
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == FTP_ERR)
    return (FTP_ERR);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -FTP_ERR)
    {
      if (close(fd) == FTP_ERR)
	return (FTP_ERR);
      return (FTP_ERR);
    }
  if (listenServer(fd) == FTP_ERR)
    return (FTP_ERR);
  if (acceptServer(fd) == FTP_ERR)
    return (FTP_ERR);
  if (close(fd) == FTP_ERR)
    return (FTP_ERR);
  return (FTP_OK);
}

int	main(int ac, char **av)
{
  if (checkArg(ac, av) == FTP_ERR)
    return (FTP_ERR);
  createServer(atoi(av[1]));
  return (FTP_OK);
}
