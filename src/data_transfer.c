/*
** data_transfer.c for  in /home/rezard/PSU_2016_myftp/src
**
** Made by rezard
** Login   <rezard@epitech.net>
**
** Started on  Thu May 18 12:02:51 2017 rezard
** Last update Thu May 18 16:09:25 2017 hazer
*/

#include <myftp.h>

int	do_pasv(t_client *client)
{
  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  if (client->tokenInfo != NULL)
    {
      dprintf(client->fd, ERR_501);
      return (FTP_ERR);
    }
  return (FTP_OK);
}

int	do_port(t_client *client)
{
  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  if (checkScndArg(client) == FTP_ERR)
    return (FTP_ERR);
  return (FTP_OK);
}

int	do_dele(t_client *client)
{
  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  if (checkScndArg(client) == FTP_ERR)
    return (FTP_ERR);
  if (unlink(client->tokenInfo) == FTP_ERR)
    return (FTP_ERR);
  dprintf(client->fd, CWD_OK);
  return (FTP_OK);
}
