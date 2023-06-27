/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:45:38 by maricard          #+#    #+#             */
/*   Updated: 2023/06/27 18:51:49 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

void	clean_g_minishell(void)
{
	int	i;

	i = 0;
	while (g_minishell.input[i])
	{
		free(g_minishell.input[i]);
		i++;
	}
	free(g_minishell.input);
	g_minishell.input = NULL;
}

// free open pipes previous allocations
void	free_open_pipes(int **pipe)
{
	int	i;

	i = 0;
	while (pipe[i])
	{
		free(pipe[i]);
		i++;
	}
	free(pipe);
}

// clean function for parser
void	clean_parser(t_parsed **parsed)
{
	t_file	*tmp;
	int		i;
	int		j;

	i = -1;
	while (parsed && parsed[++i])
	{
		j = -1;
		if (parsed[i]->cmd)
			free(parsed[i]->cmd);
		while (parsed[i]->args[++j])
			free(parsed[i]->args[j]);
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
	if (str)
		free(str);
	if (g_minishell.input)
		clean_g_minishell();
	if (g_minishell.token)
		clean_lexer(g_minishell.token);
	if (g_minishell.fd)
		clean_fd_list(g_minishell.fd);
	if (g_minishell.parsed)
		clean_parser(g_minishell.parsed);
	if (g_minishell.str2)
		clean_duplicate_array(g_minishell.str2);
	g_minishell.n_tokens2 = 0;
}
