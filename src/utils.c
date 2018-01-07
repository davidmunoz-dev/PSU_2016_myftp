/*
** utils.c for  in /home/hazer/PSU_2016_myftp/src
**
** Made by hazer
** Login   <hazer@epitech.net>
**
** Started on  Tue May  9 16:17:17 2017 hazer
** Last update Wed May 10 19:19:34 2017 rezard
*/

#include <myftp.h>

int	checkLogged(t_client *client)
{
  if (client->logged == false)
    {
      dprintf(client->fd, ERR_530);
      return (FTP_ERR);
    }
  return (FTP_OK);
}

int	checkScndArg(t_client *client)
{
  if (client->tokenInfo == NULL)
    {
      dprintf(client->fd, ERR_501);
      return (FTP_ERR);
    }
  return (FTP_OK);
}
