/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:20:40 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 21:56:49 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// return the value of the mains file descriptors
void	return_fds(void)
{
	dup2(g_minishell.out2, STDOUT_FILENO);
	close(g_minishell.out2);
	dup2(g_minishell.in2, STDIN_FILENO);
	close(g_minishell.in2);
}

// function to open pipes
int	**open_pipes(void)
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
	int	pid;
	int	status;

	status = get_builtin_type(args[0]);
	if (g_minishell.n_tokens2 == 1 && status != 0)
	{
		execute_builtin_command(args);
		return ;
	}
	signal(SIGINT, sigint_handler);
	pid = fork();
	if (pid == 0)
	{
		if (status != 0)
		{
			execute_builtin_command(args);
			exit(g_minishell.exit_status);
		}
		else
			execute_execve(args);
		g_minishell.flag2 = 0;
	}
	return ;
}

// handler for execution in pipes
void	execute_commands(t_parsed *temp, t_file *file, t_fd **fd)
{
	if (file == NULL)
	{
		execve_or_builtin(temp->args);
		if (g_minishell.pipe_flag == 0 && temp->next == NULL)
			return_fds();
		return ;
	}
	while (file != NULL)
	{
		if (file->type == GREATER)
			redirect_in(temp, &file, fd);
		else if (file->type == SMALLER)
			redirect_out(temp, &file, fd);
		else if (file->type == APPEND)
			append(temp, &file, fd);
		else if (file->type == HERE_DOC)
			here_doc_handler(temp, &file, fd);
		file = file->next;
		if (file == NULL && temp->next == NULL)
			return_fds();
	}
}
