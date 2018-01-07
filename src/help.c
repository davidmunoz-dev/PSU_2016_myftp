/*
** help.c for  in /home/rezard/PSU_2016_myftp/src
**
** Made by rezard
** Login   <rezard@epitech.net>
**
** Started on  Wed May 10 19:24:57 2017 rezard
** Last update Thu May 18 18:14:02 2017 hazer
*/

#include <myftp.h>

int	do_quit(t_client *client)
{
  if (client->tokenInfo != NULL)
    {
      dprintf(client->fd, ERR_501);
      return (FTP_ERR);
    }
  client->quit = true;
  dprintf(client->fd, QUIT);
  return (FTP_OK);
}

int	do_help(t_client *client)
{
  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  dprintf(client->fd, "214 ");
  dprintf(client->fd, HELP);
  dprintf(client->fd, HELP2);
  return (FTP_OK);
}

int	do_noop(t_client *client)
{
  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  if (client->tokenInfo != NULL)
    {
      dprintf(client->fd, ERR_501);
      return (FTP_ERR);
    }
  dprintf(client->fd, NOOP);
  return (FTP_OK);
}
