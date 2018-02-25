##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## juniqu_v
##

NAME		= zia

TEST 		= unitTest

PACKAGE		= package

RM		= rm -f

CXX		= g++

CXXFLAGS	+= -g3 -Wall -Wextra -Werror -Wfatal-errors -MD -std=c++17 -Iincludes/ -Iincludes/server -Iincludes/server/api -Iincludes/server/error -I./includes/server/NetStack -Iincludes/modules -g3

LDFLAGS		+= -ldl

SRCS		= $(foreach dir,$(shell find sources/server -type d),$(wildcard $(dir)/*.cpp)) \
					sources/main.cpp

SRCS_TEST =  $(foreach dir,$(shell find sources/server -type d),$(wildcard $(dir)/*.cpp)) \
					sources/unitTest/unitTest.cpp

OBJS_TEST = $(SRCS_TEST:.cpp=.o)
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
	@$(RM) $(OBJS_TEST)
	cd sources/modules && make clean

fclean: clean
	@echo "Cleaning executable..."
	@$(RM) $(NAME)
	@$(RM) $(TEST)
	cd sources/modules && make fclean
	@make -C $(PACKAGE) clean

re: fclean all

test: $(OBJS_TEST)
	@$(CXX) -o $(TEST) $(OBJS_TEST) $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	@echo "=>" $<
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

-include $(DEPS)

.PHONY:	all clean fclean re
