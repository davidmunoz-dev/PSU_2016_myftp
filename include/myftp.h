/*
** myftp.h for  in /home/hazer/PSU_2016_myftp/include
**
** Made by hazer
** Login   <hazer@epitech.net>
**
** Started on  Tue May  9 16:09:11 2017 hazer
** Last update Thu May 18 18:17:39 2017 hazer
*/

#ifndef _MY_FTP_H_
# define _MY_FTP_H_

#define _POSIX_C_SOURCE  200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>

#define	FTP_OK	0
#define	FTP_ERR	-1
#define	LIMITED_CLIENT	42

#define RED             "\033[1;31m"
#define GREEN           "\033[1;32m"
#define PURPLE          "\033[1;35m"
#define CYAN            "\033[1;36m"
#define BROWN           "\033[0;33m"
#define BLUE            "\033[1;34m"
#define YELLOW          "\033[1;33m"
#define BLANK           "\033[0m"

#define	CMDS	"USER PASS CWD CDUP QUIT DELE PWD PASV PORT HELP NOOP RETR STOR LIST"
#define CMDN	14

#define NOOP	"200 Command okay.\r\n"
#define QUIT	"221 Service closing control connection.\r\n"
#define LOG_OK	"230 User logged in, proceed. Logged out if appropriate.\r\n"
#define	CWD_OK	"250 Requested file action okay, completed.\r\n"
#define CWD_ERR	"550 Requested action not taken. File unavailable\r\n"
#define ERR_430 "430 Invalid username or password\r\n"
#define ERR_500 "500 Command not found.\r\n"
#define ERR_501	"501 Syntax error in parameters or arguments.\r\n"
#define	ERR_503	"503 Bad sequence of commands.\r\n"
#define	ERR_50X	"50X You are already connected. Disconnect to connect with another username.\r\n"
#define ERR_530	"530 Not logged in.\r\n"
#define	USERNAME_OK	"331 User name okay, need password.\r\n"

#define	HELP	BROWN"\"The following are the FTP commands from client to server:\n\n\tUSER <SP> <username> <CRLF>\t: Specify user for authentication\n\tPASS <SP> <password> <CRLF>\t: Specify password for authentication\n\tCWD  <SP> <pathname> <CRLF>\t: Change working directory\n\tCDUP <CRLF>\t\t\t: Change working directory to parent directory\n\tQUIT <CRLF>\t\t\t: Disconnection\n\tDELE <SP> <pathname> <CRLF>\t: Delete file on the server\n\tPWD  <CRLF>\t\t\t: Print working directory\n\tPASV <CRLF>\t\t\t: Enable \"passive\" mode for data transfer\n"

#define	HELP2	BROWN"\tPORT <SP> <host-port> <CRLF>\t: Enable \"active\" mode for data transfer\n\tHELP [<SP>]<CRLF>\t\t: List available commands\n\tNOOP <CRLF>\t\t\t: Do nothing\n\tRETR <SP> <pathname> <CRLF>\t: Download file from server to client\n\tSTOR <SP> <pathname> <CRLF>\t: Upload file from client to server\n\tLIST [<SP> <pathname>] <CRLF>\t: List files in the current working directory\"\n\r"BLANK

typedef struct	s_client
{
  bool		logged;
  bool		isGoodCmd;
  bool		quit;
  char const	*ip;
  char		*username;
  char		*password;
  char		*cmd;
  char		*token;
  char		*tokenInfo;
  char		*bufferToken;
  int		(*cmdAvailable[CMDN])(struct s_client *);
  int		typeCmd;
  int		port;
  int		fd;
}		t_client;

/* main.c */
int     createServer(int port);
int     listenServer(int fd);
int     acceptServer(int fd);

/* client.c */
void    initClient(t_client *client);
int     handleClient(t_client *client);

/* user.c */
int     do_user(t_client *client);
int	do_password(t_client *client);
int     do_cwd(t_client *client);
int     do_cdup(t_client *client);
int	do_pwd(t_client *client);

/* help.c */
int     do_quit(t_client *client);
int	do_help(t_client *client);
int     do_noop(t_client *client);

/* utils.c */
int     checkLogged(t_client *client);
int     checkScndArg(t_client *client);

/* list.c */
int     do_list(t_client *client);
int     do_stor(t_client *client);

/* dataTransfert.c */
int	do_pasv(t_client *client);
int	do_port(t_client *client);
int	do_dele(t_client *client);

/* retr.c */
int     do_retr(t_client *client);

#endif /* _MY_FTP_H_ */
