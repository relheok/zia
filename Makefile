##
## Makefile for arcade in /home/maxoulak/work/B4/C++/cpp_arcade/
##
## Made by Maxime Maisonnas
## Login   <maxime.maisonnas@epitech.eu>
##
## Started on  Mon Mar  6 11:20:32 2017 Maxime Maisonnas
## Last update Thu Apr  6 19:18:35 2017 Steven Syp
##


NAME	= zia

CC	= g++

RM	= rm -f

DIR		= sources/api/

CXXFLAGS += -Iincludes/api/ -W -Wall -Wextra -std=c++17 #-Werror

LDFLAGS = -ldl

SRCS	= $(DIR)main.cpp						\
				$(DIR)ModuleLauncher.cpp	\

OBJS	= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	cd $(DIR)modules && make

clean:
	@$(RM) $(OBJS)
	@cd $(DIR)modules && make clean

fclean: clean
	@$(RM) $(NAME)
	@cd $(DIR)modules && make fclean

re: fclean all
	cd $(DIR)modules && make re

.PHONY: all clean fclean re
