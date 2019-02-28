# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amontano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/17 11:15:45 by amontano          #+#    #+#              #
#    Updated: 2019/02/17 11:15:46 by amontano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++11

SRC = Calc.cpp Exceptions.cpp TOperand.cpp OperandFactory.cpp main.cpp Lexer.cpp

$(NAME):
	@ $(CC) $(CFLAGS) $(SRC) -o $(NAME)
	@ echo $(NAME) created.

all: $(NAME)

clean:
	@ rm -rf $(NAME)
	
fclean: clean

re: fclean all

