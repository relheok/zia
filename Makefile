##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## juniqu_v
##

NAME		= zia

PACKAGE		= package

RM		= rm -f

CXX		= g++

CXXFLAGS	+= -Wall -Wextra -Werror -Wfatal-errors -MD -std=c++17 -Iincludes/server -Iincludes/server/api -Iincludes/server/error -I./includes/server/NetStack

LDFLAGS		+= -ldl

SRCS		= $(foreach dir,$(shell find sources/server -type d),$(wildcard $(dir)/*.cpp))

OBJS		= $(SRCS:.cpp=.o)
DEPS		= $(SRCS:.cpp=.d)

all: $(NAME)
	cd sources/modules && make

$(NAME): $(OBJS)
	@echo "Building $(NAME)..."
	@$(CXX) -o $(NAME) $(OBJS) $(CXXFLAGS) $(LDFLAGS)
	@cp $(NAME) $(PACKAGE)
	@make -C $(PACKAGE)

clean:
	@echo "Cleaning temporary files..."
	@$(RM) $(OBJS)
	@$(RM) $(DEPS)
	cd sources/modules && make clean

fclean: clean
	@echo "Cleaning executable..."
	@$(RM) $(NAME)
	cd sources/modules && make fclean
	@make -C $(PACKAGE) clean

re: fclean all

%.o: %.cpp
	@echo "=>" $<
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

-include $(DEPS)

.PHONY:	all clean fclean re
