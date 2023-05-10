# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: filipa <filipa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 10:28:04 by maricard          #+#    #+#              #
#    Updated: 2023/05/10 21:37:48 by filipa           ###   ########.fr        #
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
		./srcs/history/history.c \
		./srcs/history/history2.c \
		./srcs/utils/signal.c \
		./srcs/utils/tests.c \
		./srcs/utils/variables.c \
		./srcs/utils/utils.c 

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

