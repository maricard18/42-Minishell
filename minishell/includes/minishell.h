/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:34:12 by maricard          #+#    #+#             */
/*   Updated: 2023/05/23 11:15:40 by maricard         ###   ########.fr       */
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
# include <errno.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

# define B "\033[1m\033[30m"
# define R "\033[1m\033[31m"
# define G "\033[1m\033[32m"
# define Y "\033[1m\033[33m"
# define BL "\033[1m\033[34m"
# define P "\033[1m\033[35m"
# define CYAN "\033[1m\033[36m"
# define W "\033[1m\033[37m"
# define RT "\033[0m"

// # define PROMPT "\x1b[32m[\x1b[33mMinishell\x1b[32m]~>\x1b[0m "
# define PROMPT " [MINI\033[31;1mSHELL] $ \033[0m"

enum tokens{
	PIPE,
	OR,
	AND,
	GREATER,
	SMALLER,
	APPEND,
	HERE_DOC,
	OPEN_PAR,
	CLOSE_PAR,
	STRING,
};

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

typedef enum e_builtin_types
{
    CD = 1,
    ENV,
    PWD,
    ECHO_,
    EXIT,
    UNSET,
    EXPORT
} 			t_builtin_types;

// Structs
typedef struct	s_token
{
	int				n_tokens;
	enum tokens		type;
	char			*value;
	int				index;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_file
{
	enum tokens		type;
	char			*name;
	struct s_file	*next;
}					t_file;

typedef struct s_parsed
{
	int			exec;
	int			in_file;
	int			out_file;
	char		*cmd;//command
	char		**args;//arguments
	t_token		*paranthesis;
	struct s_parsed	**parantheses_and_or;//parantheses and or
	t_file		file;
	struct s_parsed	*prev;
	struct s_parsed	*next;
}				t_parsed;

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
	char    	**input;
	int			n_tokens;
	int			index;
	struct s_parsed	**parsed_commands;
	struct s_token	*tokens;
	t_token		token;
	t_parsed	parsed;
}               t_minishell_state;

extern t_minishell_state g_minishell;

// Src
void		minishell_init(char **env);
void		lexer(char *str);
int 		validate_syntax(t_token *my_tokens);
t_parsed	**parse_commands(int in_file, int out_file, t_token *token_sequence);


// Utils
int		count_tokens2(char *str, int i);
int		store_values2(char *str, int i);
int		skip_quotes(char *str, int i);
void	clean_all(char *str);
void	update_path_directories(void);
int		number_args_env_Var(void);
void	free_array(char **arr);
int 	handle_error(int error_code, char *custom_message);

// Tokeniser
int		is_whitespace(char c);
int 	is_string(char *str);
void 	special_chars(char *str);
int 	ft_strchr2(const char *s, char c);
int		ft_strchr3(const char *s, char c, char d);
int 	ft_strchr4(const char *s, char c);
void	check_for_redirect_in(char *str);
void	check_for_redirect_out(char *str);
void	check_for_pipes(char *str);
void	check_for_string(char *str);
void	check_for_(char *str);
void	check_for_parentheses(char *str);
void	check_for_and(char *str);
void	tokeniser(t_token *temp);

// Execution 
void	execution(void);
void    execute_commands(void);
void    execute_execve(char **args);
void	execute_builtin_command(char **arguments);
char    *ft_strtok(char *str, char delimeter);
void    redirect_in();
void    redirect_out();
void    append();
void    here_doc();
void    pipe_handle();

//utils utils2.c
char *ft_strcpy(char *dest, const char *src);

//Commands
void	cd_command(char **input);
void	echo_command(char **input);
void	env_command(void);
void	exit_command(char **input);
void	pwd_command(void);
void	unset_command(char **input);
void	export_command(char **input);

//signals
void    ctrl_c(int signal);

//Parser utils
void 		skip_to_matching_parenthesis(t_token **command_token_list);
void 		handle_paranthesis(t_token **tokens_list, t_parsed **command);
void 		dd_command_to_list(t_parsed *current_command, t_parsed **command_list);
t_parsed 	*allocate_and_init_command(int in_file, int out_file);
int 		count_and_or_tokens(t_token *command_token_list);


void get_next_token(t_token *command_table);


// Tests
void    lexer_test(void);
void    ctrl_d(char *str);

//tests filipa

int carater_especial(char c);
int ve_se_tem_na_string(char *string, char *chars_to_search, size_t size);
int encontra_o_par(char *input, char c);
int retorna_strings(char *input);
int adiciona_token_a_lista(char *input, t_token *tokens_list, enum tokens type, int size);
void analisa_e_atribui_significado(char *input, t_token *tokens_list);
t_token *identificar_agrupar_tokens(char *input);


//utils
char *ft_strcpy(char *dest, const char *src);

#endif