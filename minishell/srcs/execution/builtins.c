/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:32:36 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 15:57:47 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// buitlin commands checker
int	get_builtin_type(char *command)
{
	if (!command)
		return (0);
	if (!ft_strcmp(command, "cd"))
		return (CD);
	if (!ft_strcmp(command, "env"))
		return (ENV);
	if (!ft_strcmp(command, "pwd"))
		return (PWD);
	if (!ft_strcmp(command, "echo"))
		return (ECHO);
	if (!ft_strcmp(command, "exit"))
		return (EXIT);
	if (!ft_strcmp(command, "unset"))
		return (UNSET);
	if (!ft_strcmp(command, "export"))
		return (EXPORT);
	return (0);
}

// buitin commands handler
void	execute_builtin_command(char **arguments)
{
	int	type;

	type = get_builtin_type(arguments[0]);
	if (type == CD)
		cd_command(arguments);
	else if (type == ENV)
		env_command(arguments);
	else if (type == PWD)
		pwd_command();
	else if (type == ECHO)
		echo_command(arguments);
	else if (type == EXIT)
		exit_command(arguments);
	else if (type == UNSET)
		unset_command(arguments);
	else if (type == EXPORT)
		export_command(arguments);
}
