/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:09:19 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 15:46:53 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handler command before the pipe
void	write_process(t_parsed *temp, int pipe_fd)
{
	dup2(pipe_fd, STDOUT_FILENO);
	execute_commands(temp);
	close(pipe_fd);
}

// handler command after the pipe
void	read_process(t_parsed *temp, int pipe_fd)
{
	dup2(pipe_fd, STDIN_FILENO);
	execute_commands(temp);
	close(pipe_fd);
}
