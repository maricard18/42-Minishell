/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:09:19 by maricard          #+#    #+#             */
/*   Updated: 2023/06/10 18:39:32 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// handler command before the pipe
void	write_process(t_parsed *temp, int pipe_fd)
{
	dup2(pipe_fd, STDOUT_FILENO);
	execute_commands(temp, temp->file);
	close(pipe_fd);
}

// handler command after the pipe
void	read_process(t_parsed *temp, int pipe_fd)
{
	dup2(pipe_fd, STDIN_FILENO);
	execute_commands(temp, temp->file);
	close(pipe_fd);
}
