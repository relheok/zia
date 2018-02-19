##
## Makefile for  in /home/albert_q/rendu/Tech3/Zia/cpp_zia
##
## Made by Quentin Albertone
## Login   <albert_q@epitech.net>
##
## Started on  Wed Jan 10 14:50:08 2018 Quentin Albertone
## Last update Mon Feb 12 17:20:41 2018 Quentin Albertone
##

CPP     =       g++

RM      =       \rm -f

NAME    =       netStack

SRCS    =      	src/Network/Client.cpp		\
		src/Network/Request.cpp		\
		src/Network/Network.cpp		\
		src/Network/Balancer.cpp	\
		src/Network/Worker.cpp		\
		src/Network/main.cpp		\


OBJS    =       $(SRCS:.cpp=.o)

CFLAGS  =       -W -Wall -Werror -Wextra -I./include/Network

all:	    	$(NAME)

$(NAME):       	$(OBJS)
		@echo -e "\e[0m"
		@$(CPP) $(OBJS) -o $(NAME)
		@echo -e "\e[32mAll done ! ==>\e[33m" $(NAME) "\e[32mcreated !\e[0m"

clean:
		@echo -en "\e[0mCleaning .o files..."
		@$(RM) $(OBJS)
		@echo -e "	 [\e[32mOk !\e[39m]\e[0m"

fclean:		clean
		@echo -en "\e[39mCleaning executable..."
		@$(RM) $(NAME)
		@echo -e "   [\e[32mOk !\e[39m]\e[0m"

re:	     fclean all

.cpp.o:%.cpp
		@$(CPP) -c $< -o $@ $(CFLAGS) && \
		echo -e "\e[32m[OK]" $< "\e[93m"|| \
		echo -e "\e[91;5m[ERR]\e[25m" $< "\e[93m"

.PHONY:		 all clean fclean re
