/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:48:22 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 11:14:46 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit the shell
void	exit_the_shell(int pipe_nbr)
{
	if (pipe_nbr == 1)
	{
		printf("exit\n");
		clean_all(g_minishell.str);
		clean_the_mess();
		exit(g_minishell.exit_status);
	}
}

// count the number of arguments
int	number_args(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}

// check if exit has arguments and handle them
void	check_exit_args(char **input, int pipe_nbr)
{
	if (number_args(input) > 2)
	{
		print_error(NULL, "exit\nexit: too many arguments\n", 1);
		if (pipe_nbr == 1)
		{
			clean_all(g_minishell.str);
			clean_the_mess();
			exit(1);
		}
	}
	else
	{
		g_minishell.exit_status = ft_atoi(input[1]) % 256;
		if (pipe_nbr == 1)
		{
			clean_all(g_minishell.str);
			clean_the_mess();
			exit(g_minishell.exit_status);
		}
	}
}

// check if argument has a option
int	number_signal(char *arg)
{
	while (*arg)
	{
		if ((*arg >= '0' && *arg <= '9') || *arg == '+' || *arg == '-')
			arg++;
		else
			return (0);
	}
	return (1);
}

// exits the program immediately
void	exit_command(char **input)
{
	int	pipe_nbr;

	pipe_nbr = g_minishell.n_tokens2;
	if (number_args(input) == 1)
		exit_the_shell(pipe_nbr);
	else
	{
		if (number_signal(input[1]))
		{
			check_exit_args(input, pipe_nbr);
		}
		else
		{
			print_error(NULL, "exit\nexit: numeric argument required\n", 2);
			if (pipe_nbr == 1)
			{
				clean_all(g_minishell.str);
				clean_the_mess();
				exit(2);
			}
		}
	}
}
