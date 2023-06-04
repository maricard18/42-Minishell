/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:00:53 by filipa            #+#    #+#             */
/*   Updated: 2023/06/03 20:12:06 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_state g_minishell;

int	check_if_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

// main program
int	main(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;
	char	*str;

	minishell_init(envp);
	while (1)
	{
		signal(SIGINT, &ctrl_c);
        signal(SIGQUIT, SIG_IGN);
		str = readline(PROMPT);
		g_minishell.str = str;
		ctrl_d(str);
		if (check_if_empty(str) == 1)
			continue ;
		initialize_shell(str);
		clean_all(str);
	}
	return(0);
}
