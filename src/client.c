/*
** client.c for  in /home/rezard/PSU_2016_myftp/src
**
** Made by rezard
** Login   <rezard@epitech.net>
**
** Started on  Tue May  9 22:15:20 2017 rezard
** Last update Thu May 18 16:53:27 2017 hazer
*/

#include <myftp.h>

void	initClient(t_client *client)
{
  client->quit = false;
  client->isGoodCmd = false;
  client->logged = false;
  client->username = NULL;
  client->password = NULL;
  client->cmd = NULL;
  client->token = NULL;
  client->port = -1;
  client->typeCmd = -1;
  client->cmdAvailable[0] = &do_user;
  client->cmdAvailable[1] = &do_password;
  client->cmdAvailable[2] = &do_cwd;
  client->cmdAvailable[3] = &do_cdup;
  client->cmdAvailable[4] = &do_quit;
  client->cmdAvailable[5] = &do_dele;
  client->cmdAvailable[6] = &do_pwd;
  client->cmdAvailable[7] = &do_pasv;
  client->cmdAvailable[8] = &do_port;
  client->cmdAvailable[9] = &do_help;
  client->cmdAvailable[10] = &do_noop;
  client->cmdAvailable[11] = &do_retr;
  client->cmdAvailable[12] = &do_stor;
  client->cmdAvailable[13] = &do_list;
}

void	parseCmd(char *cmd, t_client *client)
{
  if ((strncmp(cmd, "\n", 1) == 0)
      || (strncmp(cmd, "\r", 1)) == 0)
    {
      dprintf(client->fd, ERR_500);
      return ;
    }
  cmd = strtok(cmd, "\n\r");
  client->cmd = strdup(cmd);
  if ((client->token = strtok(cmd, " \t")) == NULL)
    {
      dprintf(client->fd, ERR_500);
      return ;
    }
  cmd = NULL;
  client->tokenInfo = strtok(cmd, " \t");
  cmd = NULL;
  if ((client->bufferToken = strtok(cmd, " \t")) != NULL)
    {
      dprintf(client->fd, ERR_500);
      return ;
    }
}

int	getCmd(t_client *client)
{
  char	*cmdToken;
  char	*token;
  int	typeCmd;

  cmdToken = strdup(CMDS);
  token = strdup(" ");
  typeCmd = 0;
  while ((token = strtok(cmdToken, " ")) != NULL)
    {
      if (strncmp(token, client->token, strlen(token)) == 0)
	{
	  client->cmdAvailable[typeCmd](client);
	  client->isGoodCmd = true;
	}
      cmdToken = NULL;
      typeCmd++;
    }
  if (client->isGoodCmd == false)
    dprintf(client->fd, ERR_500);
  return (FTP_OK);
}

int	handleClient(t_client *client)
{
  FILE		*F_fd;
  size_t	size;
  char		*cmd;

  size = 0;
  initClient(client);
  printf("Connection from: %s\n", client->ip);
  dprintf(client->fd, "220 Welcome ! Your IP address is : %s\n", client->ip);
  F_fd = fdopen(client->fd, "rw");
  while (client->quit == false)
    {
      cmd = NULL;
      if (getline(&cmd, &size, F_fd) > 0)
	{
	  parseCmd(cmd, client);
	  getCmd(client);
	  client->isGoodCmd = false;
	}
      else
	client->quit = true;
    }
  fclose(F_fd);
  shutdown(client->fd, SHUT_RDWR);
  free(cmd);
  return (FTP_OK);
}
