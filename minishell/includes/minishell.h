/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:34:12 by maricard          #+#    #+#             */
/*   Updated: 2023/05/11 18:13:48 by maricard         ###   ########.fr       */
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

typedef enum e_builtin_types
{
    CD = 1,
    ENV,
    PWD,
    ECHO_,
    EXIT,
    UNSET,
    EXPORT
} t_builtin_types;

enum errors{
	FILE_NOT_FOUND = 1,
	SYNTAX_ERROR = 2,
	PERM_DENIED = 4,
	CMD_NOT_FOUND = 127,
	SYSTEM_ERR = -1,
	MEMORY_ERR = -2,
	DUP_ERR = -3,
	FORK_ERR = -4,
	PIPE_ERR = -5
};

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
void			update_path_directories(void);
int				number_args_env_Var(void);
void			free_array(char **arr);
int 			handle_error(int error_code, char *custom_message);
void    		ctrl_c(int signal);
void    		ctrl_d(char *str);

//Commands
void	cd_command(char **input);
void	echo_command(char **input);
void	env_command(void);
void	exit_command(char **input);
void	pwd_command(void);
void	unset_command(char **input);
void	export_(char **input);


// Tests
void    lexer_test(t_token *token);

#endif