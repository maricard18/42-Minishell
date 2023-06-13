/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:51:04 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 12:02:40 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// skip quotes in input string
int	skip_quotes(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

// ft_strchr variation to check next character
int	ft_strchr2(const char *s, char c)
{
	if (s[0] == c)
	{
		if (s[1] == c)
			return (2);
		return (1);
	}
	return (0);
}
