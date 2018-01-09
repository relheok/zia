##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## juniqu_v
##

NAME		= module_manager

RM		= rm -f

CXX		= g++

CXXFLAGS	+= -g3 -Wall -Wextra -Werror -Wfatal-errors -MD -std=c++17 -I includes

SRCS		= $(foreach dir,$(shell find srcs -type d),$(wildcard $(dir)/*.cpp))

OBJS		= $(SRCS:.cpp=.o)
DEPS		= $(SRCS:.cpp=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building $(NAME)..."
	@$(CXX) -o $(NAME) $(OBJS) $(CXXFLAGS)

clean:
	@echo "Cleaning temporary files..."
	@$(RM) $(OBJS)
	@$(RM) $(DEPS)

fclean: clean
	@echo "Cleaning executable..."
	@$(RM) $(NAME)

re: fclean all

%.o: %.cpp
	@echo "=>" $<
	@$(CXX) -c $< -o $@ $(CXXFLAGS) $(GRAPHICFLAGS) $(AIFLAGS)

-include $(DEPS)

.PHONY:	all clean fclean re
