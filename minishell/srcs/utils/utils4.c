/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:57 by maricard          #+#    #+#             */
/*   Updated: 2023/06/15 17:28:21 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if there is a n in the input
int	check_while_n(char **input, int *i, int *a)
{
	if (input[*i][++(*a)] == 'n')
	{
		while (input[*i][*a] == 'n')
			(*a)++;
		return (1);
	}
	else
		return (0);
}

// count the number of characters until the next character c
int	ft_strclen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}
