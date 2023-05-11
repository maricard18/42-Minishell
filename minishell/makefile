# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 10:28:04 by maricard          #+#    #+#              #
#    Updated: 2023/05/10 20:58:54 by maricard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf

NAME = minishell
LIBFT = ./libft/libft.a
INCLUDES = includes

SRC = 	./srcs/lexer.c \
		./srcs/lexer2.c \
		./utils/signal.c \
		./utils/variables.c \
		./utils/tests.c

SRC-OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(SRC-OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC-OBJ) main.c $(LIBFT) -o $(NAME) -I $(INCLUDES) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(SRC-OBJ)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

leaks:
#	valgrind --leak-check=full ./$(NAME) $(ARGS)

run:
	./minishell

re: fclean all