/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:51:04 by maricard          #+#    #+#             */
/*   Updated: 2023/05/16 17:54:20 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
