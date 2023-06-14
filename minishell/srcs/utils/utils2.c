/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:51:04 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 10:28:26 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// syntax for export
void	sort_and_print(void)
{
	sort_env_variables(g_minishell.ev);
	export_print_all();
}

// check if there is an equal sign in the string
int	check_for_equal_sign(char *str, int *error)
{
	int	i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
	{
		if (*error == 0)
			print_error(NULL, "error: export bad syntax\n", 1);
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (*error == 0)
				print_error(NULL, "error: export bad syntax\n", 1);
			return (0);
		}
		i++;
	}
	if (ft_strchr3(&str[i], '=') == 1)
		return (1);
	return (0);
}

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

// ft_strchr variation to check next character
int	ft_strchr3(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
