/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:50:03 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 14:53:12 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return token index to store in args array
int	store_values2(char *str, int i)
{
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = skip_quotes(str, i);
			if (str[i] == '|' || str[i] == '<' || str[i] == '>')
				return (i - 1);
		}
		else if (str[i] == '|')
			return (i);
		else if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			return (i);
		}
		else if (str[i + 1] == '|')
			return (i);
		else if (str[i + 1] == '<' || str[i + 1] == '>')
			return (i);
		else
			i++;
	}
	return (i - 1);
}

// return next token index to count tokens
int	count_tokens2(char *str, int i)
{
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = skip_quotes(str, i);
			if (str[i] == '|' || str[i] == '<' || str[i] == '>')
				return (i);
		}
		else if (str[i] == '|')
			return (++i);
		else if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			return (++i);
		}
		else if (str[i + 1] == '|')
			return (++i);
		else if (str[i + 1] == '<' || str[i + 1] == '>')
			return (++i);
		else
			i++;
	}
	return (i);
}
