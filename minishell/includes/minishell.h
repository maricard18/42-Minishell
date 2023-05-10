/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipa <filipa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:34:12 by maricard          #+#    #+#             */
/*   Updated: 2023/05/10 20:27:52 by filipa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
#include <fcntl.h>
#include <termios.h>

// # define PROMPT "\x1b[32m[\x1b[33mMinishell\x1b[32m]~>\x1b[0m "
# define PROMPT " [MINI\033[31;1mSHELL] $ \033[0m"


# define HIST_FILE		"./.minishell_history"
# define HIST_SIZE		20

// Structs
typedef struct s_token
{
	char    **args;
	int		n_tokens;
	int		index;
}			t_token;

typedef struct s_history_node
{
	void            *content;
	struct s_history_node  *next;
	struct s_history_node  *previous;
}               	t_history_node;

typedef struct s_terminal_control
{
	char			*up_key;
	char			*down_key;
	char			*cariage_return;
	char			*clear_line;
	char			*keyend;
	char			*keystart;
}	t_terminal_control;

typedef struct s_minishell_state
{
	char            	*input;
	int             	status;
	int             	status_signal;
	char            	**environment_variables;
	char            	*pwd;
	int             	fd_in;
	int             	fd_out;
	int             	any_redirection;
	int             	is_interactive;
	struct termios  	origin;
	struct termios  	modified;
	t_terminal_control	*term_control;
	t_history_node      *history_head;
	t_history_node      *history_index;
	t_token		 		token;
}                       t_minishell_state;


// Src
void	minishell_init(t_minishell_state *shell, char **env);
void	lexer(char *str, t_token *token);
void	initialize_history(t_minishell_state *data);
int	set_history_mode(t_minishell_state *data);


// Utils
void	signal_handling(void);
t_history_node	*ft_lstnew_2(void *content);
void	free_data(t_minishell_state *data, int exit_code);

// Tests
void    lexer_test(t_token *token);

#endif