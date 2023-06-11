/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:48:22 by maricard          #+#    #+#             */
/*   Updated: 2023/06/11 12:31:40 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit the shell
void	exit_the_shell(void)
{
	printf("exit\n");
	clean_all(g_minishell.str);
	clean_the_mess();
	exit(g_minishell.exit_status);
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
	if (number_args(input) == 1)
		exit_the_shell();
	else
	{
		if (number_signal(input[1]))
		{
			if (number_args(input) > 2)
			{
				print_error(NULL, "exit\nexit: too many arguments\n", 1);
				clean_all(g_minishell.str);
				clean_the_mess();
				exit(1);
			}
			g_minishell.exit_status = ft_atoi(input[1]) % 256;
			clean_all(g_minishell.str);
			clean_the_mess();
			exit(g_minishell.exit_status);
		}
		print_error(NULL, "exit\nexit: numeric argument required\n", 2);
		clean_all(g_minishell.str);
		clean_the_mess();
		exit(2);
	}
}
