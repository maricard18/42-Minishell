/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:20:40 by maricard          #+#    #+#             */
/*   Updated: 2023/06/07 13:57:58 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

char *search_expansions(char **env, char *str)
{
	char 	*temp;
	char	*new_str;
	int		i;
	
	temp = ft_calloc(1, sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			temp = ft_strjoin(temp, handle_env_variables(env, str, &i));
		}
		new_str = ft_strjoin(temp, ft_char_string(str[i]));
		temp = ft_strdup(new_str);
		free(new_str);
		i++;
	}
	return (temp);
}

// function to close pipes
void	close_pipes(int *pipe_fd)
{
	int	i;
	int	a;

	i = (g_minishell.n_tokens2 - 1) * 2;
	a = 0;
	while (a < i)
	{
		close(pipe_fd[a]);
		printf("closed pipe[%d]\n", a);
		a++;
	}
}

// function to open pipes
int		**open_pipes()
{
	int	**pipe_fd;
	int	i;
	int	a;

	i = (g_minishell.n_tokens2 - 1);
	pipe_fd = ft_calloc(i + 1, sizeof(int *));
	a = -1;
	while (++a < i)
	{
		pipe_fd[a] = malloc(sizeof(int) * 2);
		pipe(pipe_fd[a]);
	}
	return (pipe_fd);
}

// check if its a builtin command or not
void	execve_or_builtin(char **args)
{
	if (get_builtin_type(args[0]) != 0)
		execute_builtin_command(args);
	else if (ft_strcmp(args[0], "$?") == 0)
	{
		printf("%d: command not found\n", g_minishell.exit_status);
	}
	else
		execute_execve(args);
}

// handler for execution in pipes
void	execute_commands(t_parsed *temp)
{
	t_file	*file;

	file = temp->file;
	if (file == NULL)
	{
		execve_or_builtin(temp->args);
	}
	while (file != NULL)
	{
		if (file->type == GREATER)
			redirect_in(temp, file);
		else if (file->type == SMALLER)
			redirect_out(temp, file);
		else if (file->type == APPEND)
			append(temp, file);
		else if (file->type == HERE_DOC)
			here_doc(temp, file->name);
		file = file->next;
	}
}
