/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:29:23 by maricard          #+#    #+#             */
/*   Updated: 2023/05/16 17:57:02 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

void	print_list_types()
{
	t_token *temp;
	
	temp = &g_minishell.token;
	printf("[List types] ");
	while (temp)
	{
		printf(""R"["RT"%d"R"]"RT" ", temp->type);
		temp = temp->next;
	}
	printf("\n");
}

void	print_list_values()
{
	t_token *temp;
	
	temp = &g_minishell.token;
	printf("[List values] ");
	while (temp)
	{
		printf(""R"["RT"%s"R"]"RT" ", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

void	print_list_index()
{
	t_token *temp;
	
	temp = &g_minishell.token;
	printf("[List index] ");
	while (temp)
	{
		printf(""R"["RT"%d"R"]"RT" ", temp->index);
		temp = temp->next;
	}
	printf("\n");
}

void	print_string_array()
{
	int	i;
	
	i = 0;
	printf("[String array] ");
	while (g_minishell.input[i])
	{
		printf(""R"["RT"%s"R"]"RT" ", g_minishell.input[i]);
		i++;
	}
	printf("\n");	
}

// test for lexer and tokanizer
void    lexer_test()
{
	printf("\n"R"--> [LEXER TEST] <--"RT"\n\n");
	printf("[Number of tokens: "G"%d"RT"]\n", g_minishell.n_tokens);
	print_string_array();
	print_list_index();
	print_list_values();
	print_list_types();
	printf ("\n");
}
