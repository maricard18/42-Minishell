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

# define READ_END 0
# define WRITE_END 1

// handler execuntion to pipes
void	write_to_pipe(t_parsed **temp, int **pipe_fd, int i)
{
	if (temp[i + 1] == NULL)
	{
		dup2(g_minishell.out_file, STDOUT_FILENO);
		execute_commands(temp[i]);
		close(g_minishell.out_file);
		close(pipe_fd[i - 1][READ_END]);
		return ;
	}
	else
	{
		dup2(pipe_fd[i][WRITE_END], STDOUT_FILENO);
		execute_commands(temp[i]);
		close(pipe_fd[i][WRITE_END]);
	}
	if (i > 0)
		close(pipe_fd[i - 1][READ_END]);
}

// handler connection in pipes
void	connect_pipes(t_parsed **temp, int **pipe_fd, int i)
{
	(void) temp;
	if (temp[i] == NULL)
	{
		dup2(g_minishell.in_file, STDIN_FILENO);
		close(g_minishell.in_file);
		return ;
	}
	if (i > 0)
		dup2(pipe_fd[i - 1][READ_END], STDIN_FILENO);
}

// handler pipes
void	pipe_handling(t_parsed **temp)
{
	int	i;
	int **pipe_fd;

	i = 0;
	pipe_fd = open_pipes();
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
		execute_commands(temp[0]);
		dup2(g_minishell.out_file, STDOUT_FILENO);
		close(g_minishell.out_file);
		dup2(g_minishell.in_file, STDIN_FILENO);
		close(g_minishell.in_file);
	}
	while (waitpid(0, &g_minishell.exit_status, 0) > 0)
		continue ;
	if (WIFEXITED(g_minishell.exit_status))
			g_minishell.exit_status = WEXITSTATUS(g_minishell.exit_status);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
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
