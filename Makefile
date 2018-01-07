##
## Makefile for  in /home/hazer/PSU_2016_myftp
## 
## Made by hazer
## Login   <hazer@epitech.net>
## 
## Started on  Tue May  9 16:03:04 2017 hazer
## Last update Thu May 18 12:02:45 2017 rezard
##

TARGET	 = server

CC	 = gcc

SRC      = main.c		\
	   client.c		\
	   user.c		\
	   error.c		\
	   utils.c		\
	   help.c		\
	   list.c		\
	   data_transfer.c	\
	   retr.c		\

CFLAGS   += -W -Wall -ansi -pedantic -Iinclude

SRCDIR	 = src
OBJDIR	 = obj

SOURCES  := $(addprefix src/, $(SRC))

OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

rm       = rm -rf
mkdir    = mkdir -p

$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(CFLAGS)
	@echo $(TARGET)" compiled !"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(mkdir) $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all     : $(TARGET)

clean   :
	@$(rm) $(OBJDIR)
	@echo "Binary files deleted"

fclean  : clean
	@$(rm) $(TARGET) $(LINK)
	@echo "Binary and executable files are deleted"

re      : fclean all

.PHONY: all clean fclean re
