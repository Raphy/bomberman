##
## Makefile for  in /home/svirch_n/bomberman/TestBomberman
## 
## Made by nicolas svirchevsky
## Login   <svirch_n@epitech.net>
## 
## Started on  Mon May 19 15:46:31 2014 nicolas svirchevsky
## Last update Wed May 21 15:34:34 2014 nicolas svirchevsky
##

NAME		=	bomberman

SRC		=	main.cpp

OBJ		=	$(SRC:.cpp=.o)

CC		=	/usr/bin/g++

CPPFLAGS	=	-W -Wextra -Wall -std=c++11
CPPFLAGS	+=	-I LibBomberman_linux_x64/includes/

RM		=	rm -f

LIB		=	-L LibBomberman_linux_x64/libs/
LIB		+=	-lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread -ldl

ECHO		=	echo -e

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CC) $(OBJ) $(CPPFLAGS) -o $(NAME) $(LIB)
			@echo -e '\nEnvironment variable:\nexport LD_LIBRARY_PATH=./LibBomberman_linux_x64/libs'

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean re
