/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:34:12 by maricard          #+#    #+#             */
/*   Updated: 2023/05/10 10:53:39 by maricard         ###   ########.fr       */
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

// # define PROMPT "\x1b[32m[\x1b[33mMinishell\x1b[32m]~>\x1b[0m "
# define PROMPT " [MINI\033[31;1mSHELL] $ \033[0m"

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
	struct s_hlist  *next;
	struct s_hlist  *previous;
}               	t_history_node;

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
//	struct termios  	origin;
//	struct termios  	modified;
//	t_terminal_control	*termc;
	t_history_node      *history_head;
	t_history_node      *history_index;
	t_token		 		token;
}                       t_minishell_state;

// Src
void	minishell_init(t_minishell_state *shell, char **env);
void	lexer(char *str, t_token *token);

// Utils
void	signal_handling(void);

// Tests
void    lexer_test(t_token *token);

#endif