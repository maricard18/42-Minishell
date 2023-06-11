/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:07:47 by maricard          #+#    #+#             */
/*   Updated: 2023/06/11 12:41:25 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initialize shell
void	initialize_shell(char *str)
{
	char	**temp;
	t_token	*token;

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
	//printf("       [" G "SYNTAX OK" RT "]\n");
	parse_commands(0, 1, token);
	//parser_test();
	execution();
	add_history(str);
}
