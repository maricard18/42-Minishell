/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:15:05 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 20:27:52 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// wheck if there is a next node
void	check_for_next_node(t_parsed *temp, t_file **file, t_fd **fd)
{
	if ((*file)->next != NULL)
	{
		*file = (*file)->next;
		execute_commands(temp, *file, fd);
		return ;
	}
	execve_or_builtin(temp->args);
}

// create a string
char	*create_string(char *temp, char c)
{
	char	*char_str;
	char	*new_str;

	char_str = ft_char_string(c);
	new_str = ft_strjoin(temp, char_str);
	temp = ft_strdup(new_str);
	free(new_str);
	free(char_str);
	return (temp);
}

// function to handle env variables inside here doc
char	*search_expansions(char **env, char *str)
{
	char	*temp;
	char	*var;
	int		i;

	temp = ft_calloc(1, sizeof(char));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			i++;
			var = handle_env_variables(env, str, &i);
			temp = ft_strjoin(temp, var);
			free(var);
		}
		if (str[i] == '\0')
			break ;
		if (str[i] == '$')
			continue ;
		temp = create_string(temp, str[i]);
	}
	return (temp);
}

// here doc execution
void	exec_here_doc(char **env, int pipe_fd, t_file **file, char *str)
{
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			print_error((*file)->name, ": Not found\n", 0);
			free(str);
			break ;
		}
		if (ft_strcmp(str, (*file)->name) == 0)
		{
			if (check_next_node(file) == 0)
			{
				free(str);
				break ;
			}
			else
				continue ;
		}
		str = search_expansions(env, str);
		if ((*file)->next == NULL || (*file)->next->type != HERE_DOC)
			write_here_doc(pipe_fd, str);
		free(str);
	}
}

// here doc handler
void	here_doc(t_parsed *temp, t_file **file, t_fd **fd)
{
	int		pipe_fd[2];
	char	**env;
	char	*str;

	str = NULL;
	dup2((*fd)->out, STDOUT_FILENO);
	dup2((*fd)->in, STDIN_FILENO);
	env = g_minishell.ev;
	pipe(pipe_fd);
	exec_here_doc(env, pipe_fd[1], file, str);
	close(pipe_fd[1]);
	close((*fd)->out);
	close((*fd)->in);
	*fd = (*fd)->next;
	dup2(temp->out_file, STDOUT_FILENO);
	dup2(temp->in_file, STDIN_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	if (temp->args[0])
	{
		check_for_next_node(temp, file, fd);
	}
	close(pipe_fd[0]);
}
