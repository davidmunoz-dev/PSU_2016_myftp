/*
** retr.c for  in /home/rezard/PSU_2016_myftp/src
**
** Made by rezard
** Login   <rezard@epitech.net>
**
** Started on  Wed May 10 21:33:52 2017 rezard
** Last update Wed May 10 21:35:06 2017 rezard
*/

#include <myftp.h>

int	do_retr(t_client *client)
{
  if (checkLogged(client) == FTP_ERR)
    return (FTP_ERR);
  if (checkScndArg(client) == FTP_ERR)
    return (FTP_ERR);
  return (FTP_OK);
}
