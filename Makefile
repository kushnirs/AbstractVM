# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/02 10:58:17 by skushnir          #+#    #+#              #
#    Updated: 2018/07/10 11:01:51 by skushnir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= avm

CC			= clang++

CFLAGS		= -Wall -Wextra -Werror

SRC			= main.cpp Operand.cpp IOperand.cpp

OBJ			= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lncurses 

$(OBJ): %.o : %.cpp
	$(CC) $(CFLAGS) -c $< 
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.NOTPARALLEL: all $(NAME) re