# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/02 10:58:17 by skushnir          #+#    #+#              #
#    Updated: 2018/07/12 09:32:22 by skushnir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= avm

CC			= clang++

CFLAGS		= -Wall -Wextra -Werror -std=c++11

SRC			= main.cpp AVM.cpp

OBJ			= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ): %.o : %.cpp
	$(CC) $(CFLAGS) -c $< 
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.NOTPARALLEL: all $(NAME) re