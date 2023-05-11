/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:34:12 by maricard          #+#    #+#             */
/*   Updated: 2023/05/11 15:19:15 by maricard         ###   ########.fr       */
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
# include <fcntl.h>
# include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>

// # define PROMPT "\x1b[32m[\x1b[33mMinishell\x1b[32m]~>\x1b[0m "
# define PROMPT " [MINI\033[31;1mSHELL] $ \033[0m"

// Structs
typedef struct	s_token
{
	char    **args;
	int		n_tokens;
	int		index;
}				t_token;

typedef struct s_sig
{
	int		ctrl_c;
	int		ctrl_d;
}				t_sig;

typedef struct s_minishell_state
{
	int			ignore;
	int			opening_prompt;
	int			parent_pid;
	int			*child_pids;
	int			child_pids_count;
	int			in_file;
	int			out_file;
	char		**ev;
	char		**paths;
	t_token		token;
	
}                       t_minishell_state;

extern t_minishell_state g_minishell;


// Src
void	minishell_init(char **env);
void	lexer(char *str, t_token *token);


// Utils
void			signal_handling(void);
int     		count_tokens2(char *str, int i);
int     		store_values2(char *str, int i);
int     		skip_quotes(char *str, int i);
void    		clean_all(t_token *token);

// Tests
void    lexer_test(t_token *token);

#endif