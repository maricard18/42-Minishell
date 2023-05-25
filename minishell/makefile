# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 10:28:04 by maricard          #+#    #+#              #
#    Updated: 2023/05/25 17:54:56 by maricard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf

NAME = minishell
LIBFT = ./libft/libft.a
INCLUDES = includes
LIBS = -ltermcap -lreadline -lncurses
MK = --no-print-directory

SRC = 	./srcs/parser/lexer.c \
		./srcs/parser/lexer2.c \
		./srcs/parser/tokeniser.c \
		./srcs/utils/clean.c \
		./srcs/utils/signal.c \
		./srcs/utils/variables.c \
		./srcs/utils/utils.c \
		./srcs/utils/utils2.c \
		./srcs/utils/utils3.c \
		./srcs/utils/types.c \
		./srcs/utils/types2.c \
		./srcs/utils/erro.c \
		./srcs/commands/cd.c \
		./srcs/commands/echo.c \
		./srcs/commands/env.c \
		./srcs/commands/exit.c \
		./srcs/commands/export.c \
		./srcs/commands/pwd.c \
		./srcs/commands/unset.c \
		./srcs/execution/execution.c \
		./srcs/execution/execve.c \
		./srcs/execution/builtins.c \
		./srcs/execution/redirect.c \
		./srcs/execution/pipes.c \
		./srcs/parser/initialize.c \
		./srcs/parser/syntax.c \
		./srcs/parser/parser.c \
		./srcs/parser/parser_utils.c \
		./srcs/utils/test_lex.c \
		./srcs/utils/test_utils.c \
		./srcs/utils/test_pars.c 
#		./srcs/parser/parser_extras_for_testes.c

SRC-OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	@echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)libft/*$(RESET)"
	make $(MK) -C ./libft

$(NAME): $(SRC-OBJ) $(LIBFT)
	@echo "[$(CYAN)Linking$(RESET)] $(GREEN)*$(RESET)"
	$(CC) $(CFLAGS) $(SRC-OBJ) main.c $(LIBFT) -o $(NAME) -I $(INCLUDES) $(LIBS)
	
	@echo "[$(GREEN)Done$(RESET)]"
	
%.o: %.c
	@echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	@echo "[$(RED)Cleaned$(RESET)] $(GREEN)*/*.o$(RESET)"
	make $(MK) clean -C ./libft
	$(RM) $(SRC-OBJ)

fclean: clean
	@echo "[$(RED)Deleted$(RESET)] $(GREEN)$(NAME)$(RESET)"
	make $(MK) fclean -C ./libft
	$(RM) $(NAME)

leaks:
#	valgrind --leak-check=full ./$(NAME) $(ARGS)

run:
	./minishell

re: fclean all

