/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:57:46 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 15:20:22 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// check the special characters
void	special_chars(char *str, int k, t_token *temp)
{
	int		res;

	res = check_for_quotes(k, temp);
	if (res == 0)
		res = check_for_pipes(str, temp);
	if (res == 0)
		res = check_for_redirect_in(str, temp);
	if (res == 0)
		res = check_for_redirect_out(str, temp);
	if (res == 0)
		temp->type = STRING;
}

void	init_values(t_token *temp)
{
	temp->value = NULL;
	temp->index = 0;
	temp->prev = NULL;
	temp->next = NULL;
}

// atribute values to the arguments
void	tokeniser(char **str)
{
	int		i;
	t_token	*new;
	t_token	*temp;

	i = 0;
	temp = NULL;
	new = malloc(sizeof(t_token));
	while (str[i])
	{
		init_values(new);
		new->value = ft_strdup(str[i]);
		special_chars(str[i], i, new);
		new->index = i;
		if (temp != NULL)
			new->prev = temp;
		else
			g_minishell.token = new;
		if (str[i + 1])
			new->next = malloc(sizeof(t_token));
		temp = new;
		new = new->next;
		i++;
	}
}
