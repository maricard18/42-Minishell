/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:45:38 by maricard          #+#    #+#             */
/*   Updated: 2023/06/07 14:28:47 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// clean function for parser
void	clean_parser(t_parsed **parsed)
{
	t_file *tmp;
	int	i;
	int	j;

	i = 0;
	while (parsed && parsed[i])
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
		tmp = parsed[i]->file;
		while (parsed[i]->file != NULL)
		{
			free(parsed[i]->file->name);
			tmp = parsed[i]->file->next;
			free(parsed[i]->file);
			parsed[i]->file = tmp;
		}
		free(parsed[i]);
		i++;
	}
	free(parsed);
	g_minishell.parsed = NULL;
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
	g_minishell.token = NULL;
}

// main clean function
void	clean_all(char *str)
{
	char		**temp;
	t_token		*token;
	t_parsed	**parsed;

	temp = g_minishell.input;
	token = g_minishell.token;
	parsed = g_minishell.parsed;
	if (str)
		free(str);
	if (temp)
		clean_lexer(token);
	if (parsed)
		clean_parser(parsed);
}
