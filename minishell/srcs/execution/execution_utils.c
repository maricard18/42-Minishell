/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:20:40 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 13:28:49 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if its a builtin command or not
void	execve_or_builtin(char **args)
{
	if (get_builtin_type(args[0]) != 0)
		execute_builtin_command(args);
	else if (ft_strcmp(args[0], "$?") == 0)
	{
		printf("minishell: command not found: %d\n", g_minishell.exit_status);
	}
	else
		execute_execve(args);
}

// handler for execution in pipes
void	execute_commands(t_parsed *temp)
{
	t_file *file;

	file = temp->file;
	if (file == NULL)
	{
		execve_or_builtin(temp->args);
	}
	while (file != NULL)
	{
		if (file->type == GREATER)
			redirect_in(temp, file->name);
		else if (file->type == SMALLER)
			redirect_out(temp, file->name);
		else if (file->type == APPEND)
			append(temp, file->name);
		else if (file->type == HERE_DOC)
			here_doc(temp, file->name);
		file = file->next;
	}
}
