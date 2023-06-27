/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:07:47 by maricard          #+#    #+#             */
/*   Updated: 2023/06/27 18:39:28 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// duplicator of arrays
void	create_new_array(char **temp)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while (temp[i])
		i++;
	new = malloc((i + 1) * sizeof(char *));
	while (temp[j])
	{
		new[j] = ft_strdup(temp[j]);
		j++;
	}
	new[j] = NULL;
	g_minishell.str2 = new;
}

// initialize shell
void	initialize_shell(char *str)
{
	char	**temp;
	t_token	*token;

	g_minishell.flag2 = 0;
	g_minishell.error = 0;
	add_history(str);
	lexer(str);
	temp = g_minishell.input;
	if (check_unfinished_quotes(temp) == 1)
		return ;
	create_new_array(temp);
	search_env_vars(temp);
	tokeniser(temp);
	token = g_minishell.token;
	if (validate_syntax(token) == 1)
		return ;
	parse_commands(0, 1, token);
	execution();
}
