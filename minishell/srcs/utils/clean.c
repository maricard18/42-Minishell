/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:45:38 by maricard          #+#    #+#             */
/*   Updated: 2023/06/07 11:05:31 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// clean function for parser
void	clean_parser(t_parsed **parsed)
{
	int	i;
	int	j;

	i = 0;
	while (parsed[i])
	{
		j = 0;
		if (parsed[i]->cmd)
			free(parsed[i]->cmd);
		while (parsed[i]->args[j])
		{
			free(parsed[i]->args[j]);
			j++;
		}
		free(parsed[i]->args);
		while (parsed[i]->file != NULL)
		{
			free(parsed[i]->file->name);
			free(parsed[i]->file);
			parsed[i]->file = parsed[i]->file->next;
		}
		free(parsed[i]);
		i++;
	}
	free(parsed);
}

// clean function for lexer and tokanizer
void	clean_lexer(t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	i = 0;
	while (i < g_minishell.n_tokens)
	{
		free(g_minishell.input[i]);
		i++;
	}
	free(g_minishell.input);
	i = 0;
	while (i < g_minishell.n_tokens)
	{
		free(token->value);
		tmp = token->next;
		free(token);
		token = tmp;
		i++;
	}
}

// main clean function
void	clean_all(char *str)
{
	if (str)
		free(str);
	if (g_minishell.input)
		clean_lexer(g_minishell.token);
	if (g_minishell.parsed)
		clean_parser(g_minishell.parsed);
}
