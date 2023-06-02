/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:11:25 by mariohenriq       #+#    #+#             */
/*   Updated: 2023/06/02 18:19:55 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle expansion in double quotes
char	*double_quotes(char **env, char *input, int *i)
{
	char	*new_str;
	char	*var;

	new_str = ft_strdup("");
	new_str = ft_strjoin(new_str, ft_char_string(input[*i]));
	(*i)++;
	while (input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			(*i)++;
			var = handle_env_variables(env, input, i);
				// missing a free on "var"
			new_str = ft_strjoin(new_str, var);
		}
		if (!input[*i])
			return (new_str);
		new_str = ft_strjoin(new_str, ft_char_string(input[*i]));
		(*i)++;
	}
	if (input[*i] == '"')
	{
		new_str = ft_strjoin(new_str, ft_char_string(input[*i]));
		(*i)++;
	}
	return (new_str);
}

// handle expansion in single quotes
char	*single_quotes(char *input, int *i)
{
	char *new_str;
	int j;

	j = *i;
	(*i)++;
	while (input[*i] != '\'')
	{
		(*i)++;
	}
	if (input[*i] == '\'')
		(*i)++;
	new_str = ft_substr(input, j, *i - j);
	return (new_str);
}