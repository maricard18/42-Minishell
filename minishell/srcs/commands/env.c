/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipa <filipa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:45:11 by maricard          #+#    #+#             */
/*   Updated: 2023/06/11 09:30:08 by filipa           ###   ########.fr       */
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
		printf("env: %s: No such file or directory\n", arguments[1]);
		g_minishell.exit_status = 127;
		return ;
	}
	sort_env_variables(env);
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
