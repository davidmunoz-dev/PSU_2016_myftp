/*
** user.c for  in /home/rezard/PSU_2016_myftp/src
**
** Made by rezard
** Login   <rezard@epitech.net>
**
** Started on  Wed May 10 17:55:41 2017 rezard
** Last update Thu May 18 18:18:02 2017 hazer
*/

#include <myftp.h>

int	do_user(t_client *client)
{
  if (checkScndArg(client) == FTP_ERR)
    return (FTP_ERR);
  if (client->logged == true)
    {
      dprintf(client->fd, ERR_501);
      return (FTP_ERR);
    }
  client->username = client->tokenInfo;
  dprintf(client->fd, USERNAME_OK);
  return (FTP_OK);
}

int	do_password(t_client *client)
{
  if (client->logged == true)
    {
      dprintf(client->fd, ERR_501);
      return (FTP_ERR);
    }
  if (client->username == NULL)
    dprintf(client->fd, ERR_503);
  if (strncmp(client->username, "Anonymous", 9) == 0
      && client->tokenInfo == NULL)
    {
      client->password = NULL;
      client->logged = true;
      dprintf(client->fd, LOG_OK);
    }
  else
    dprintf(client->fd, ERR_530);
  return (FTP_OK);
}

int	do_cwd(t_client *client)
{
  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  if (checkScndArg(client) == FTP_ERR)
    return (FTP_ERR);
  if (chdir(client->tokenInfo) < 0)
    {
      dprintf(client->fd, CWD_ERR);
      return (FTP_ERR);
    }
  dprintf(client->fd, CWD_OK);
  return (FTP_OK);
}

int	do_cdup(t_client *client)
{
  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  if (client->tokenInfo != NULL)
    {
      dprintf(client->fd, ERR_501);
      return (FTP_ERR);
    }
  if (chdir("..") < 0)
    {
      dprintf(client->fd, CWD_ERR);
      return (FTP_ERR);
    }
  dprintf(client->fd, NOOP);
  return (FTP_OK);
}

int	do_pwd(t_client *client)
{
  char buffer[UCHAR_MAX];

  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  if (client->tokenInfo != NULL)
    {
      dprintf(client->fd, ERR_501);
      return (FTP_ERR);
    }
  if (getcwd(buffer, UCHAR_MAX) == NULL)
    return (FTP_ERR);
  dprintf(client->fd, "257 \"%s\"\r\n", buffer);
  return (FTP_OK);
}
