/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:45:11 by maricard          #+#    #+#             */
/*   Updated: 2023/06/01 18:11:04 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print ambient variables
void	env_command(void)
{
	char	**env;

	env = g_minishell.ev;//array de variáveis de ambiente armazenado em g_minishell.ev
	while (*env)
	{
		printf("%s\n", *env);//imprime cada variável de ambiente
		env++;
	}
	if (g_minishell.parent_pid != getpid())
		exit(0);
}
