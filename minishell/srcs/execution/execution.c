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

extern t_minishell_state g_minishell;

// handler execuntion to pipes
void    write_to_pipe(t_parsed **temp, int *pipe_fd, int i)
{
	if (temp[i + 1] == NULL)
	{
		execute_commands(temp[i]);
		close(g_minishell.out_file);
	}
	else if (i % 2 == 1)
        write_process(temp[i], pipe_fd[3]);
	else if (i % 2 == 0)
        write_process(temp[i], pipe_fd[1]);
}

// handler connection in pipes
void    connect_pipes(t_parsed **temp, int *pipe_fd, int i)
{
    if (i % 2 == 1)
	{
        dup2(pipe_fd[0], STDIN_FILENO);
		if (temp[i + 1] == NULL)
			close(g_minishell.in_file);
	}
	else if (i % 2 == 0)
	{
        dup2(pipe_fd[2], STDIN_FILENO);
		if (temp[i + 1] == NULL)
			close(g_minishell.in_file);
	}
}

// handler pipes
void    pipe_handling(t_parsed **temp)
{
    int i;
    int pipe_fd[4];

    i = 0;
    pipe(pipe_fd);
    if (temp[i + 2] == NULL)
    {
        write_process(temp[i], pipe_fd[1]);
        read_process(temp[i + 1], pipe_fd[0]);
		close(g_minishell.out_file);
		close(g_minishell.in_file);
		return ;
    }
	pipe(pipe_fd + 2);
    while (temp[i])
    {
        write_to_pipe(temp, pipe_fd, i);
        if (temp[i + 1] == NULL)
			return ;
		i++;
        connect_pipes(temp, pipe_fd, i);
	}
}

// check what function to execute
void    check_command(t_parsed **temp)
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
			close(g_minishell.out_file);
			close(g_minishell.in_file);
		}
    }
}

// execute the input given
void    execution()
{
    //int pid;
    //int status;
    t_parsed **temp;

    temp = g_minishell.parsed;
	g_minishell.in_file = dup(STDIN_FILENO);
	g_minishell.out_file = dup(STDOUT_FILENO);
    //pid = fork();
    //if (pid == 0)
	//{
        check_command(temp);
	//	exit(0);
	//}
	//else
    //    waitpid(pid, &status, 0);
}