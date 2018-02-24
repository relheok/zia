##
## Makefile for arcade in /home/maxoulak/work/B4/C++/cpp_arcade/
##
## Made by Maxime Maisonnas
## Login   <maxime.maisonnas@epitech.eu>
##
## Started on  Mon Mar  6 11:20:32 2017 Maxime Maisonnas
## Last update Mon Apr  3 21:38:13 2017 Maxime Maisonnas
##

NAME	= libssl_module.so

NAMEPHP	= libphp_module.so

NAMELOG = liblog_module.so

CC	= g++

RM	= rm -f

CXXFLAGS += -I../../includes/modules/ -I../../includes/server/api/ -I../../includes/server -W -Wall -Wextra -std=c++17 #-Werror

LDFLAGS	 += -lssl -lcrypto

# Flags lib dynamique
CXXFLAGS += -fPIC -c
LDFLAGS	+= -shared

SRCS	= SSLModule.cpp


SRCSPHP = phpcpp.cpp

SRCSLOG = LogModule.cpp

OBJS	= $(SRCS:.cpp=.o)

OBJSPHP	= $(SRCSPHP:.cpp=.o)

OBJSLOG = $(SRCSLOG:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS) $(OBJSLOG)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	$(CC) $(OBJSLOG) -o $(NAMELOG) $(LDFLAGS)
##	$(CC) $(OBJSPHP) -o $(NAMEPHP) $(LDFLAGS)

clean:
	@$(RM) $(OBJS) $(OBJSPHP)

fclean: clean
	@$(RM) $(NAME) $(NAMEPHP)

re: fclean all

.PHONY: all clean fclean re
