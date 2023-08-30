/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:09:10 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 12:56:58 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// copy string
char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// token counter
int	token_counter(char **str)
{
	int	i;
	int	a;

	i = 1;
	a = 0;
	while (str[i])
	{
		if (str[i][0] == '|')
			a++;
		i++;
	}
	if (a == 0)
	{
		g_minishell.n_tokens2 = 1;
		return (1);
	}
	else
		g_minishell.n_tokens2 = a + 1;
	return (g_minishell.n_tokens2);
}

// modify string
void	modify_string(char **old_str, char **new_str)
{
	free(*old_str);
	*old_str = ft_strdup(*new_str);
	free(*new_str);
}

// one char string
char	*ft_char_string(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

// join two strings without free
char	*ft_strjoin2(char const *s1, char const *s2)
{
	int		i;
	int		a;
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	i = ft_strlen(s1);
	a = ft_strlen(s2);
	str = malloc((a + i) * sizeof(char) + 1);
	if (!str)
		return (0);
	i = 0;
	a = 0;
	while (s1[i])
		str[a++] = s1[i++];
	i = 0;
	while (s2[i])
		str[a++] = s2[i++];
	str[a] = '\0';
	return (str);
}
