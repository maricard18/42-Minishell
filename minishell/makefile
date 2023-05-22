# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 10:28:04 by maricard          #+#    #+#              #
#    Updated: 2023/05/22 16:31:26 by maricard         ###   ########.fr        #
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
		./srcs/parser/values.c \
		./srcs/parser/parser.c \
		./srcs/parser/initialize.c \
		./srcs/parser/parser_extras_for_testes.c \
		./srcs/parser/parser_utils.c \
		./srcs/utils/clean.c \
		./srcs/utils/signal.c \
		./srcs/utils/tests.c \
		./srcs/utils/variables.c \
		./srcs/utils/utils.c \
		./srcs/utils/utils2.c \
		./srcs/utils/special_chars.c \
		./srcs/utils/special_chars2.c \
		./srcs/utils/erro.c \
		./srcs/commands/command_handler.c \
		./srcs/commands/cd.c \
		./srcs/commands/echo.c \
		./srcs/commands/env.c \minishell/includes/minishell.h: needs merge
minishell/main.c: needs merge
minishell/makefile: needs merge
minishell/srcs/parser/values.c: needs merge
minishell/srcs/utils/utils2.c: needs merge
error: you need to resolve your current index first

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

