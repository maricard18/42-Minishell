/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:20 by maricard          #+#    #+#             */
/*   Updated: 2023/06/10 19:35:36 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// here doc execution
void	exec_here_doc(char **env, int pipe_fd, t_file **file)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			print_error((*file)->name, ": Not found\n", 1);
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
	}
}

// here doc handler
void	here_doc(t_parsed *temp, t_file **file)
{
	int		pipe_fd[2];
	char	**env;

	env = g_minishell.ev;
	pipe(pipe_fd);
	exec_here_doc(env, pipe_fd[1], file);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	if (temp->args[0] && (*file)->next == NULL)
		execve_or_builtin(temp->args);
	close(pipe_fd[0]);
}

// append handler
void	append(t_parsed *temp, t_file **file)
{
	int	file_fd;

	file_fd = open((*file)->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file_fd == -1)
	{
		perror("error opening file\n");
		exit(1);
	}
	if ((*file)->next == NULL || (*file)->next->type != APPEND)
	{
		dup2(file_fd, STDOUT_FILENO);
		if ((*file)->next != NULL)
		{
			*file = (*file)->next;
			execute_commands(temp, *file);
			close(file_fd);
			return ;
		}
		else if (temp->args[0])
			execve_or_builtin(temp->args);
	}
	close(file_fd);
}

// redirect_out handler
void	redirect_out(t_parsed *temp, t_file **file)
{
	int	file_fd;

	file_fd = open((*file)->name, O_RDONLY, 0644);
	if (file_fd == -1)
	{
		print_error((*file)->name, ": Not found\n", 1);
	}
	if ((*file)->next == NULL || (*file)->next->type != SMALLER)
	{
		dup2(file_fd, STDIN_FILENO);
		if ((*file)->next != NULL)
		{
			*file = (*file)->next;
			execute_commands(temp, *file);
			close(file_fd);
			return ;
		}
		else if (temp->args[0])
			execve_or_builtin(temp->args);
	}
	close(file_fd);
}

// redirect_in handler
void	redirect_in(t_parsed *temp, t_file **file)
{
	int	file_fd;

	file_fd = open((*file)->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_fd == -1)
	{
		perror("error opening file\n");
		exit(1);
	}
	if ((*file)->next == NULL || (*file)->next->type != GREATER)
	{
		dup2(file_fd, STDOUT_FILENO);
		if ((*file)->next != NULL)
		{
			*file = (*file)->next;
			execute_commands(temp, *file);
			close(file_fd);
			return ;
		}
		else if (temp->args[0])
			execve_or_builtin(temp->args);
	}
	close(file_fd);
}
