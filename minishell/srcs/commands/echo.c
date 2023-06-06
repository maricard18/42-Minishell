/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:54:24 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 14:36:02 by maricard         ###   ########.fr       */
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
		g_minishell.flag = 1;
		write(1, &input[i], 1);
		i++;
	}
}

// check if -n option is present
int	check_n_option(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '-')
	{
		i++;
		if (input[i] == 'n')
		{
			while (input[i] == 'n')
				i++;
		}
		else
			return (0);
	}
	if (input[i] == '\0')
		return (1);
	return (0);
}

// echo handler
void	echo_command(char **input)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (input[1] != NULL)
		flag = check_n_option(input[1]);
	if (flag == 1)
		i++;
	while (input[i])
	{
		g_minishell.flag = 0;
		put_char(input[i]);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag == 0 || g_minishell.flag == 0)
		write(STDOUT_FILENO, "\n", 1);
}
