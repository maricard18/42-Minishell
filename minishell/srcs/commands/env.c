/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:45:11 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 19:35:54 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print ambient variables
void	env_command(char **arguments)
{
	char	**env;

	env = g_minishell.ev;
	if (arguments[1])
	{
		print_error(arguments[1], "error: No such file or directory.\n", 127);
		return ;
	}
	else
		g_minishell.exit_status = 0;
	sort_env_variables(env);
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
