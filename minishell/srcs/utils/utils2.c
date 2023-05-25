/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:51:04 by maricard          #+#    #+#             */
/*   Updated: 2023/05/25 16:10:17 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// skip quotes in input string
int     skip_quotes(char *str, int i)
{
    char    quote;

    quote = str[i];
    i++;
    while (str[i] && str[i] != quote)
        i++;
    if (str[i] == quote)
        i++;
    return (i);
}

// check if is a word
int is_string(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|' || str[i] == '>' || str[i] == '<' ||
                str[i] == '(' || str[i] == ')' || str[i] == '&')
		{
			if (str[i] == '&' && str[i + 1] != '&')
				return (1);	
            return (0);
		}
        i++;
    }
    return (1);
}

// ft_strchr variation to check next character
int ft_strchr2(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
        {
            if (s[i + 1] == c)
                return (2);
			return (1);
        }
		i++;
	}
	return (0);
}

// ft_strchr variation to check parentesis
int ft_strchr3(const char *s, char c, char d)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
        else if (s[i] == d)
            return (2);
		i++;
	}
	return (0);
}

// ft_strchr variation to only check next character
int ft_strchr4(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
        {
            if (s[i + 1] == c)
                return (2);
        }
		i++;
	}
	return (0);
}
