/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:48:38 by mariohenriq       #+#    #+#             */
/*   Updated: 2023/06/14 16:21:43 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// swap two strings
void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// compare two strings
int	compare_strings(const char *a, const char *b)
{
	return (ft_strcmp(a, b));
}

// sort env variables
void	sort_env_variables(char **env)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	while (env[count] != NULL)
	{
		count++;
	}
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (compare_strings(env[j], env[j + 1]) > 0)
			{
				swap_strings(&env[j], &env[j + 1]);
			}
			j++;
		}
		i++;
	}
}
