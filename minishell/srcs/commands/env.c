/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:45:11 by maricard          #+#    #+#             */
/*   Updated: 2023/06/01 13:11:38 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//// expand env variables
//void	display_env_var(char *env)
//{
//	int i;

//	i = 0;
//	while (env[i] != '=')
//		i++;
//	printf("%s\n", env[i + 1]);
//}

//// find env variables
//void	handle_env_variables(char *str, int *i)
//{
//	int j;
//	char **env;
//	char *var;

//	env = g_minishell.ev;
//	(*i)++;
//	j = *i;
//	while (is_alnum(str[*i]) == 1)
//		(*i)++;
//	var = ft_substr(str, j, *i - j);
//	printf("var: %s\n", var);
//	j = 0;
//	while (*env)
//	{
//		if (var[j] == *env[j])
//		{
//			while (var[j] == *env[j])
//			{
//				if (var[j] == '\0' && *env[j] == '=')
//				{
//					display_env_var(*env);
//					return ;
//				}
//				j++;
//			}
//		}
//		env++;
//	}
//}

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