/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:11:53 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 20:07:44 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// store tokens in args array
void	store_tokens(char *str)
{
	int	i;
	int	a;

	i = 0;
	while (g_minishell.index <= g_minishell.n_tokens)
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] != ' ')
		{
			a = i;
			i = store_values2(str, i);
			g_minishell.input[g_minishell.index] = ft_substr(str, a, (i - a)
					+ 1);
		}
		if (str[i] == '\0')
			break ;
		else
		{
			g_minishell.index++;
			i++;
		}
	}
}

// count tokens in input string
int	count_tokens(char *str)
{
	int	i;
	int	tokens;

	i = 0;
	tokens = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] != ' ')
		{
			i = count_tokens2(str, i);
			tokens++;
		}
		if (str[i] == '\0')
			break ;
	}
	return (tokens);
}

// function that devides the input string into arguments
void	lexer(char *str)
{
	g_minishell.n_tokens = count_tokens(str);
	g_minishell.input = malloc(sizeof(char *) * (g_minishell.n_tokens + 1));
	if (!g_minishell.input)
		exit(1);
	g_minishell.input[g_minishell.n_tokens] = NULL;
	g_minishell.index = 0;
	store_tokens(str);
}
