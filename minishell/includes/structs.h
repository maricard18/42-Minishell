/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:01:27 by maricard          #+#    #+#             */
/*   Updated: 2023/05/31 12:05:03 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// enums
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
	char			*value;
	int				index;
	enum tokens		type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_file
{
	enum tokens		type;
	char			*name;
	struct s_file	*next;
}				t_file;

typedef struct s_parsed
{
	int				exec;
	int				in_file;
	int				out_file;
	char			*cmd;
	char			**args;
	t_file			*file;
	t_token			*paranthesis;
	struct s_parsed	**parantheses_and_or;
	struct s_parsed *prev;
	struct s_parsed	*next;
}				t_parsed;

typedef struct	s_sig
{	
	int			ctrl_c;
	int			ctrl_d;
}				t_sig;

typedef struct s_minishell_state
{
	int				ignore;
	int				opening_prompt;
	int				parent_pid;
	int				*child_pids;
	int				child_pids_count;
	int				in_file;
	int				out_file;
	int				n_tokens;
	int				index;
    int             commands;
	char			*str;
	char			**ev;
	char			**paths;
	char    		**input;
	t_token			*token;
	t_parsed		**parsed;
}               t_minishell_state;

extern t_minishell_state g_minishell;

#endif