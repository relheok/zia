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

CC	= g++

RM	= rm -f

CXXFLAGS += -I../../includes/modules/ -I../../includes/server/api/ -W -Wall -Wextra -std=c++17 #-Werror

LDFLAGS	 += -lssl -lcrypto

# Flags lib dynamique
CXXFLAGS += -fPIC -c
LDFLAGS	+= -shared

SRCS	= SSLModule.cpp

OBJS	= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
