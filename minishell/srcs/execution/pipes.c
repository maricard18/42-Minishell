/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:06:43 by mariohenriq       #+#    #+#             */
/*   Updated: 2023/06/17 12:12:13 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// handler execuntion to pipes
void	write_to_pipe(t_parsed **temp, int **pipe_fd, int i, t_fd **fd)
{
	if (temp[i + 1] == NULL)
	{
		dup2(g_minishell.out, STDOUT_FILENO);
		temp[i]->out_file = g_minishell.out;
		execute_commands(temp[i], temp[i]->file, fd);
		close(g_minishell.out);
		close(pipe_fd[i - 1][READ_END]);
		return ;
	}
	else
	{
		dup2(pipe_fd[i][WRITE_END], STDOUT_FILENO);
		temp[i]->out_file = pipe_fd[i][WRITE_END];
		execute_commands(temp[i], temp[i]->file, fd);
		close(pipe_fd[i][WRITE_END]);
	}
	if (i > 0)
		close(pipe_fd[i - 1][READ_END]);
}

// handler connection in pipes
void	connect_pipes(t_parsed **temp, int **pipe_fd, int i)
{
	(void)temp;
	if (temp[i] == NULL)
	{
		dup2(g_minishell.in, STDIN_FILENO);
		close(g_minishell.in);
		return ;
	}
	if (i > 0)
	{
		dup2(pipe_fd[i - 1][READ_END], STDIN_FILENO);
		temp[i]->in_file = pipe_fd[i - 1][READ_END];
	}
}

// handler pipes
void	pipe_handling(t_parsed **temp, t_fd **fd)
{
	int	i;
	int	**pipe_fd;

	i = 0;
	pipe_fd = open_pipes();
	while (temp[i])
	{
		write_to_pipe(temp, pipe_fd, i, fd);
		i++;
		connect_pipes(temp, pipe_fd, i);
	}
	free_open_pipes(pipe_fd);
}
