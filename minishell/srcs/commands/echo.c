/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:54:24 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 11:47:55 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// write character
void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		write(1, &input[i], 1);
		i++;
	}
}

// check if -n option is present
void	check_n_option(char **input, int *i, int *flag)
{
	int	a;

	while (input[*i])
	{
		a = -1;
		if (input[*i][++a] == '-')
		{
			if (check_while_n(input, i, &a) == 0)
				return ;
			if (input[*i][a] != '\0')
				return ;
		}
		else
			return ;
		(*i)++;
		if (input[*i] && input[*i][0] != '-')
			break ;
		*flag = 1;
	}
	if (input[*i - 1][a] == '\0')
		*flag = 1;
}

// echo handler
void	echo_command(char **input)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (input[1] != NULL)
	{
		if (input[1][0] == '\0')
			i++;
		else
			check_n_option(input, &i, &flag);
	}
	while (input[i])
	{
		put_char(input[i]);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag == 0 || input[1] == NULL)
		write(STDOUT_FILENO, "\n", 1);
	g_minishell.exit_status = 0;
}
