/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:45:11 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 19:49:30 by maricard         ###   ########.fr       */
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
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
