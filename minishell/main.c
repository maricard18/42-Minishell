/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:00:53 by filipa            #+#    #+#             */
/*   Updated: 2023/06/27 18:40:14 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_state	g_minishell;

// check it it is a empty string
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
	char	*str;

	(void)argc;
	(void)argv;
	minishell_init(envp);
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline(PROMPT);
		g_minishell.str = str;
		ctrl_d(str);
		if (check_if_empty(str) == 1)
			continue ;
		initialize_shell(str);
		clean_all(str);
	}
}
