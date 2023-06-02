/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:51:08 by maricard          #+#    #+#             */
/*   Updated: 2023/05/16 20:33:02 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// handler execuntion to pipes
void	write_to_pipe(t_parsed **temp, int *pipe_fd, int i)
{
	if (temp[i + 1] == NULL)
	{
		dup2(g_minishell.out_file, STDOUT_FILENO);
		execute_commands(temp[i]);
		close(g_minishell.out_file);
	}
	else if (i % 2 == 1)
		write_process(temp[i], pipe_fd[3]);
	else if (i % 2 == 0)
		write_process(temp[i], pipe_fd[1]);
}

// handler connection in pipes
void	connect_pipes(t_parsed **temp, int *pipe_fd, int i)
{
	if (i % 2 == 1)
	{
		if (temp[i] == NULL)
		{
			dup2(g_minishell.in_file, STDIN_FILENO);
			close(g_minishell.in_file);
		}
		else
			dup2(pipe_fd[0], STDIN_FILENO);
	}
	else if (i % 2 == 0)
	{
		if (temp[i] == NULL)
		{
			dup2(g_minishell.in_file, STDIN_FILENO);
			close(g_minishell.in_file);
		}
		else
			dup2(pipe_fd[2], STDIN_FILENO);
	}
}

// handler pipes
void	pipe_handling(t_parsed **temp)
{
	int	i;
	int	pipe_fd[4];

	i = 0;
	pipe(pipe_fd);
	if (temp[i + 2] == NULL)
	{
		write_process(temp[i], pipe_fd[1]);
		dup2(g_minishell.out_file, STDOUT_FILENO);
		close(g_minishell.out_file);
		read_process(temp[i + 1], pipe_fd[0]);
		dup2(g_minishell.in_file, STDIN_FILENO);
		close(g_minishell.in_file);
		return ;
	}
	pipe(pipe_fd + 2);
	while (temp[i])
	{
		write_to_pipe(temp, pipe_fd, i);
		i++;
		connect_pipes(temp, pipe_fd, i);
	}
}

// check what function to execute
void	check_command(t_parsed **temp)
{
	if (temp[1] != NULL)
		pipe_handling(temp);
	else
	{
		if (temp[0]->file == NULL)
		{
			execve_or_builtin(temp[0]->args);
			return ;
		}
		else
		{
			execute_commands(temp[0]);
			dup2(g_minishell.out_file, STDOUT_FILENO);
			close(g_minishell.out_file);
			dup2(g_minishell.in_file, STDIN_FILENO);
			close(g_minishell.in_file);
		}
	}
}
// ! cat not working
// ! here doc not working

// execute the input given
void	execution(void)
{
	t_parsed	**temp;

	temp = g_minishell.parsed;
	g_minishell.in_file = dup(STDIN_FILENO);
	g_minishell.out_file = dup(STDOUT_FILENO);
	if (ft_strlen(g_minishell.str) == 0)
		return ;
	check_command(temp);
}
