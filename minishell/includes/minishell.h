/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: filipa <filipa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:34:12 by maricard          #+#    #+#             */
/*   Updated: 2023/05/06 18:06:26 by filipa           ###   ########.fr       */
=======
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:34:12 by maricard          #+#    #+#             */
/*   Updated: 2023/05/06 14:08:52 by maricard         ###   ########.fr       */
>>>>>>> ef150b119c54bc7542ca266bac7262852c5c3f96
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

<<<<<<< HEAD
# define PROMPT " [MINI\033[31;1mSHELL] \033[0m"

// Structs
typedef struct s_token
{
	char    *str;
	int     token_type;
}			t_token;

typedef struct s_history_node
{
	void            *content;
	struct s_hlist  *next;
	struct s_hlist  *previous;
}               	t_history_node;

typedef struct s_minishell_state
{
	char            	*prompt;
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
	t_history_node      *history_head;
	t_history_node      *history_index;
//	t_terminal_control	*termc;
	t_token		 		*token;
}                       t_minishell_state;
>>>>>>> ef150b119c54bc7542ca266bac7262852c5c3f96

#endif