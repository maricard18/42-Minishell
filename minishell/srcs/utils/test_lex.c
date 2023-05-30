/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:29:23 by maricard          #+#    #+#             */
/*   Updated: 2023/05/30 17:37:59 by maricard         ###   ########.fr       */
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
	print_string_array(g_minishell.input);
	print_list_values();
	print_list_types();
	printf("" G "--------------------------" RT "\n\n");
}
