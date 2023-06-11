/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:24:44 by maricard          #+#    #+#             */
/*   Updated: 2023/06/11 12:22:23 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return error if unifinished quotes
int	check_quotes(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (str[*i] == c)
	{
		(*i)++;
		return (0);
	}
	else
	{
		print_error(NULL, "error: unifinished quotes\n", 2);
		return (1);
	}
}

// check if quotes are unfinished
int	check_unfinished_quotes(char **str)
{
	int	i;
	int	a;

	i = 0;
	while (str[i])
	{
		a = 0;
		while (str[i][a])
		{
			if (str[i][a] == '\'')
			{
				if (check_quotes(str[i], &a, '\'') == 1)
					return (1);
			}
			else if (str[i][a] == '"')
			{
				if (check_quotes(str[i], &a, '"') == 1)
					return (1);
			}
			else
				a++;
		}
		i++;
	}
	return (0);
}
