/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:09:19 by maricard          #+#    #+#             */
/*   Updated: 2023/05/29 20:07:00 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handler command before the pipe
void    write_process(t_parsed *temp, int *pipe_fd, int a)
{
    dup2(pipe_fd[a], STDOUT_FILENO);
    execve_or_builtin(temp->args);
    close(pipe_fd[a]);
    dup2(g_minishell.out_file, STDOUT_FILENO);
    //close(g_minishell.out_file);
}

// handler command after the pipe
void    read_process(t_parsed *temp, int *pipe_fd, int a)
{
    dup2(pipe_fd[a], STDIN_FILENO);
    execve_or_builtin(temp->args);
    close(pipe_fd[a]);
    dup2(g_minishell.in_file, STDIN_FILENO);
    //close(g_minishell.in_file);
}
