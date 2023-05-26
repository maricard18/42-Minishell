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

// execute the input given
void    testing()
{
	execute_execve(g_minishell.parsed->args);
	execute_builtin_command(g_minishell.parsed->args);
    redirect_in();
	redirect_out();
	append();
	here_doc(g_minishell.parsed->args[0]);
	pipe_handle();
}

// execute the input given
void    execution()
{
    int pipe_fd[2];
    int i;
    t_parsed *temp;

    temp = g_minishell.parsed;
    i = 0;
    int commands  = 3;
    int fd_in = dup(STDIN_FILENO);
    int fd_out = dup(STDOUT_FILENO);
    if (commands > 1)
        pipe(pipe_fd);
    while (temp)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        execute_execve(temp->args);
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out); 
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        if (temp->next == NULL)
        {
            dup2(fd_in, STDIN_FILENO);
            close(pipe_fd[0]);
        }
        temp = temp->next;
        i++;
    }
}
