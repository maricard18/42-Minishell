/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:09:19 by maricard          #+#    #+#             */
/*   Updated: 2023/05/29 23:49:30 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handler command before the pipe
void    write_process(t_parsed *temp, int pipe_fd)
{
    dup2(pipe_fd, STDOUT_FILENO);
    execute_commands(temp);
    close(pipe_fd);
    dup2(g_minishell.out_file, STDOUT_FILENO);
    //close(g_minishell.out_file);
}

// handler command after the pipe
void    read_process(t_parsed *temp, int pipe_fd)
{
    dup2(pipe_fd, STDIN_FILENO);
	execute_commands(temp);
    close(pipe_fd);
    dup2(g_minishell.in_file, STDIN_FILENO);
    //close(g_minishell.in_file);
}
