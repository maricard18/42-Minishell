/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:12:41 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 14:45:26 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print t_file list
void	print_t_file(t_file *temp, int i)
{
	char	*str;

	printf("   t_file list  | ");
	if (temp == NULL)
		printf("[" G "NULL" RT "] ");
	else
	{
		while (temp)
		{
			str = check_type(temp->type);
			printf("[" G "%s" RT "] ", str);
			temp = temp->next;
		}
		printf("\n");
		temp = g_minishell.parsed[i]->file;
		printf("   t_file name  | ");
		while (temp)
		{
			printf("[" G "%s" RT "] ", temp->name);
			temp = temp->next;
		}
		printf("\n");
	}
}

// print list args
void	print_list_args(t_parsed *temp)
{
	int	i;

	i = 0;
	printf("    List args   | ");
	while (temp->args[i])
	{
		printf("[" G "%s" RT "] ", temp->args[i]);
		i++;
	}
	printf("\n");
}

// test for parser
void	parser_test(void)
{
	int			i;
	t_parsed	**temp;

	i = 0;
	temp = g_minishell.parsed;
	printf("\n" G "      ---------------      " RT "");
	printf("\n" G "----> | " RT "PARSER TEST " G "| <----" RT "\n");
	printf("" G "      ---------------      " RT "\n\n");
	while (temp[i])
	{
		printf("   List number  | [" G "%d" RT "]\n", i + 1);
		print_list_args(temp[i]);
		print_t_file(temp[i]->file, i);
		i++;
		if (temp[i])
			printf("\n---------------------------" RT "\n");
	}
	printf("\n" G "---------------------------" RT "\n\n");
}
