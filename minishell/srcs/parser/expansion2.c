/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:11:25 by mariohenriq       #+#    #+#             */
/*   Updated: 2023/06/14 15:43:03 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle expansion in double quotes
char	*double_quotes(char **env, char *input, int *i)
{
	char	*char_str;
	char	*new_str;
	char	*var;

	new_str = ft_strdup("");
	(*i)++;
	while (input[*i] != '"')
	{
		while (input[*i] == '$')
		{
			(*i)++;
			var = handle_env_variables(env, input, i);
			new_str = ft_strjoin(new_str, var);
			free(var);
		}
		if (!input[*i] || input[*i] == '"')
			return (new_str);
		char_str = ft_char_string(input[*i]);
		new_str = ft_strjoin(new_str, char_str);
		free(char_str);
		(*i)++;
	}
	if (input[*i] == '"')
		(*i)++;
	return (new_str);
}

// handle expansion in single quotes
char	*single_quotes(char *input, int *i)
{
	char	*new_str;
	int		j;

	(*i)++;
	j = *i;
	while (input[*i] != '\'')
	{
		(*i)++;
	}
	if (input[*i] == '\'')
		(*i)++;
	new_str = ft_substr(input, j, (*i - j) - 1);
	return (new_str);
}
