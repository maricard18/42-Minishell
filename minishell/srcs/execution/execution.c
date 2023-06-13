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

// check what function to execute
void	check_command(t_parsed **temp, t_fd **fd)
{
	int	status;

	status = get_builtin_type(temp[0]->args[0]);
	g_minishell.pipe_flag = 0;
	if (temp[1] != NULL)
	{
		g_minishell.pipe_flag = 1;
		pipe_handling(temp, fd);
	}
	else
		execute_commands(temp[0], temp[0]->file, fd);
	while (waitpid(0, &g_minishell.exit_status, 0) > 0)
	{
		continue ;
	}
	if (status == 0)
	{
		if (WIFEXITED(g_minishell.exit_status))
			g_minishell.exit_status = WEXITSTATUS(g_minishell.exit_status);
		else
			g_minishell.exit_status = 130;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
}

// execute the input given
void	execution(void)
{
	t_parsed	**temp;
	t_fd		*fd;

	temp = g_minishell.parsed;
	fd = g_minishell.fd;
	duplicate_fds();
	if (ft_strlen(g_minishell.str) == 0)
		return ;
	check_command(temp, &fd);
}
