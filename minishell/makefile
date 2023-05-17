# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 10:28:04 by maricard          #+#    #+#              #
#    Updated: 2023/05/17 11:11:10 by maricard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf

NAME = minishell
LIBFT = ./libft/libft.a
INCLUDES = includes
LIBS = -ltermcap -lreadline -lncurses

SRC = 	./srcs/parser/lexer.c \
		./srcs/parser/lexer2.c \
		./srcs/parser/tokeniser.c \
		./srcs/utils/clean.c \
		./srcs/utils/signal.c \
		./srcs/utils/tests.c \
		./srcs/utils/variables.c \
		./srcs/utils/utils.c \
		./srcs/utils/utils2.c \
		./srcs/utils/special_chars.c \
		./srcs/utils/special_chars2.c \
		./srcs/commands/command_handler.c \
		./srcs/commands/cd.c \
		./srcs/commands/echo.c \
		./srcs/commands/env.c \
		./srcs/commands/exit.c \
		./srcs/commands/export.c \
		./srcs/commands/pwd.c \
		./srcs/commands/unset.c \
		./srcs/execution/execution.c \
		./srcs/execution/execve.c

SRC-OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(SRC-OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC-OBJ) main.c $(LIBFT) -o $(NAME) -I $(INCLUDES) $(LIBS)

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

