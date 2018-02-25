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

CXXFLAGS	+= -g3 -Wall -Wextra -Werror -Wfatal-errors -MD -std=c++17 -Iincludes/server -Iincludes/server/api -Iincludes/server/error -I./includes/server/NetStack -Iincludes/modules -g3

LDFLAGS		+= -ldl

SRCS		= $(foreach dir,$(shell find sources/server -type d),$(wildcard $(dir)/*.cpp))

OBJS		= $(SRCS:.cpp=.o)
DEPS		= $(SRCS:.cpp=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building $(NAME)..."
	@$(CXX) -o $(NAME) $(OBJS) $(CXXFLAGS) $(LDFLAGS)
	@make -C sources/modules
	@cp $(NAME) sources/modules/*.so $(PACKAGE)
	@make -C $(PACKAGE)

clean:
	@echo "Cleaning temporary files..."
	@$(RM) $(OBJS)
	@$(RM) $(DEPS)
	@make -C sources/modules clean

fclean: clean
	@echo "Cleaning executable..."
	@$(RM) $(NAME) $(PACKAGE)/$(NAME) $(PACKAGE)/*.so
	@make -C sources/modules fclean
	@make -C $(PACKAGE) clean

re: fclean all

%.o: %.cpp
	@echo "=>" $<
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

-include $(DEPS)

.PHONY:	all clean fclean re
