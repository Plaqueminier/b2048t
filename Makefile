##
## Makefile
##

SRC	=	src/main.cpp				\
		src/Core.cpp				\
		src/Game.cpp				\
		src/UICell.cpp				\

OBJ	=			$(SRC:.cpp=.o)

CXXFLAGS	= 	-W -Wall -Wextra -std=c++14 -I./include -I./src -I./img

SFMLFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system

NAME	=			b2048t

RM	=			rm -f

all: 			$(NAME)

$(NAME): 		$(OBJ)
			g++ -o $(NAME) $(OBJ) $(CXXFLAGS) $(SFMLFLAGS)

clean:
			rm -f $(OBJ)

fclean: 		clean
			rm -f $(NAME)

re:			fclean all
