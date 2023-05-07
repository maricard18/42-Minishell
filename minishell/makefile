# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 10:28:04 by maricard          #+#    #+#              #
#    Updated: 2023/05/07 01:08:58 by maricard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

NAME = minishell
LIBFT = ./libft/libft.a
INCLUDES = includes

SRC = 	./srcs/lexer.c \
		./utils/signal.c

SRC-OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(SRC-OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC-OBJ) main.c $(LIBFT) -o $(NAME) -I $(INCLUDES) -lreadline
	./minishell

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

re: fclean all