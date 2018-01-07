/*
** error.c for  in /home/hazer/PSU_2016_myftp/src
**
** Made by hazer
** Login   <hazer@epitech.net>
**
** Started on  Tue May  9 16:17:31 2017 hazer
** Last update Thu May 18 12:04:17 2017 rezard
*/

#include <myftp.h>
#include <error.h>

void	printArgErr()
{
  printf(RED"Usage : ./server port path\n\n"BLANK);
  printf(YELLOW"\tport is the port number on which the server socket listen\n");
  printf("\tpath is the path to the home directory for the \"Anonymous\" user\n\
\n"BLANK);
}

int	checkArg(int ac, char **av)
{
  if (ac != 3 || atoi(av[1]) <= 0 || opendir(av[2]) == NULL)
    {
      if (ac != 3)
	printf(RED"server : Wrong argument number\n\n"BLANK);
      else if (atoi(av[1]) <= 0)
	printf(RED"server : Wrong port number\n\n"BLANK);
      else if (opendir(av[2]) == NULL)
	printf(RED"server : Wrong path\n\n"BLANK);
      printArgErr();
      return (FTP_ERR);
    }
  if (chdir(av[2]) != FTP_OK)
    return (FTP_ERR);
  return (FTP_OK);
}
