/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:07:47 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 11:36:56 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

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
	search_env_vars(temp);
	tokeniser(temp);
	token = g_minishell.token;
	//lexer_test();
	if (validate_syntax(token) == 1)
		return ;
	parse_commands(0, 1, token);
	//parser_test();
	execution();
}
