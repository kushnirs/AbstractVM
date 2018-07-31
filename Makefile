# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/02 10:58:17 by skushnir          #+#    #+#              #
#    Updated: 2018/07/31 12:42:47 by skushnir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	avm

CC			=	clang++

CFLAGS		=	-Wall -Wextra -Werror -std=c++1z

HDRSDIR		=	./includes

HDRS		=	$(addprefix $(HDRSDIR)/, IOperand.hpp Operand.hpp AVM.hpp)

SRCSDIR		=	./sources

SRCS		=	main.cpp AVM.cpp

OBJDIR		=	./obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HDRS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJDIR):
	@mkdir $@

$(OBJ): $(OBJDIR)/%.o : $(SRCSDIR)/%.cpp $(HDRS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I./includes

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.NOTPARALLEL: all $(NAME) re