/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:29:23 by maricard          #+#    #+#             */
/*   Updated: 2023/06/02 16:20:43 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// print list types
void	print_list_types(void)
{
	char	*str;
	t_token	*temp;

	temp = g_minishell.token;
	printf("    List types    | ");
	while (temp)
	{
		str = check_type(temp->type);
		printf("[" G "%s" RT "] ", str);
		temp = temp->next;
	}
	printf("\n");
}

// print list values
void	print_list_values(void)
{
	t_token	*temp;

	temp = g_minishell.token;
	printf("    List values   | ");
	while (temp)
	{
		printf("[" G "%s" RT "] ", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

// print strings
void	print_string_array(char **str)
{
	int	i;

	i = 0;
	printf("   String array   | ");
	while (str[i])
	{
		printf("[" G "%s" RT "] ", str[i]);
		i++;
	}
	printf("\n");
}

// test for lexer and tokanizer
void	lexer_test(void)
{
	printf("\n" G "      --------------      " RT "");
	printf("\n" G "----> | " RT "LEXER TEST " G "| <----" RT "\n");
	printf("" G "      --------------      " RT "\n\n");
	printf(" Number of tokens | [" G "%d" RT "]\n", g_minishell.n_tokens);
	printf("   Input string   | [" G "%s" RT "]\n", g_minishell.str);
	print_string_array(g_minishell.input);
	print_list_values();
	print_list_types();
	printf("" G "--------------------------" RT "\n\n");
}
