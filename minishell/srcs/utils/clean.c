/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:45:38 by maricard          #+#    #+#             */
/*   Updated: 2023/06/03 12:21:08 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// clean function for lexer and tokanizer
void    clean_lexer(t_token *token)
{
	t_token	*tmp;
    int i;

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
		tmp = tmp->next;
		free(token);
		token = tmp;
		i++;
	}
}

// main clean function
void	clean_all(char *str)
{
	t_token	*token;
	int		i;
	
	token = g_minishell.token;
	i = 0;
	if (str)
		free(str);
	if (g_minishell.input)
		clean_lexer(token);
}
