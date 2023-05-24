/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:09:19 by maricard          #+#    #+#             */
/*   Updated: 2023/05/24 19:32:34 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handler command before the pipe
void    child_process(int pipe_fd[2])
{
    int fd_out;
    
    fd_out = dup(STDOUT_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);
    execute_builtin_command(g_minishell.parsed.args);
    dup2(fd_out, STDOUT_FILENO);
    close(fd_out);
}

// handler command after the pipe
void    main_process(int pipe_fd[2])
{
    int fd_in;
    
    fd_in = dup(STDIN_FILENO);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
    execute_builtin_command(g_minishell.parsed.next->args);
    dup2(fd_in, STDIN_FILENO);
    close(fd_in);
}

// pipe handler
void    pipe_handle()
{
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
    {
        printf("pipe error\n");
        exit(1);
    }
    child_process(pipe_fd);
    main_process(pipe_fd);
}
