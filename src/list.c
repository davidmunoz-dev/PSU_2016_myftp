/*
** list.c for  in /home/rezard/PSU_2016_myftp/src
**
** Made by rezard
** Login   <rezard@epitech.net>
**
** Started on  Wed May 10 21:22:15 2017 rezard
** Last update Thu May 18 17:57:30 2017 hazer
*/

#include <myftp.h>

int	do_list(t_client *client)
{
  DIR*			ptdir;
  struct dirent*	entree;

  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  if (client->tokenInfo == NULL)
    ptdir = opendir(".");
  else
    if ((ptdir = opendir(client->tokenInfo)) == NULL)
      {
	dprintf(client->fd, CWD_ERR);
	return (FTP_ERR);
      }
  dprintf(client->fd, "150 File status okay; about to open data connection.\n\r");
  while ((entree = readdir(ptdir)) != NULL)
    {
      if (opendir(entree->d_name) != NULL)
	dprintf(client->fd, BLUE"%s\t\t"BLANK, entree->d_name);
      else
	dprintf(client->fd, "%s\t\t", entree->d_name);
    }
  dprintf(client->fd, "\n");
  dprintf(client->fd, "226 Closing data connection.\n\r");
  closedir(ptdir);
  return (FTP_OK);
}

int	do_stor(t_client *client)
{
  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  if (checkScndArg(client) == FTP_ERR)
    return (FTP_ERR);
  return (FTP_OK);
}
