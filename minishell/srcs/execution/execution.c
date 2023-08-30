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

// handler for execution in pipes
void	execute_commands(t_parsed *temp, t_file *file, t_fd **fd)
{
	if (file == NULL)
	{
		execve_or_builtin(temp->args);
		if (g_minishell.pipe_flag == 0)
			return_fds();
		else
			dup2(temp->in_file, STDIN_FILENO);
		return ;
	}
	while (file != NULL)
	{
		if (file->type == GREATER)
			redirect_in(temp, &file);
		else if (file->type == SMALLER)
			redirect_out(temp, &file);
		else if (file->type == APPEND)
			append(temp, &file);
		else if (file->type == HERE_DOC)
			here_doc(temp, &file, fd);
		if (file == NULL && temp->next == NULL)
			return_fds();
	}
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
	}
	return ;
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
		continue ;
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
	if (ft_strlen(g_minishell.str) == 0)
		return ;
	duplicate_fds(temp[0]);
	check_command(temp, &fd);
}
