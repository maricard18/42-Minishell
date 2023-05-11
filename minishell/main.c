/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:00:53 by filipa            #+#    #+#             */
/*   Updated: 2023/05/11 14:43:01 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_minishell_state g_minishell;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*str;

	minishell_init(&g_minishell, envp);
//	initialize_history(&g_minishell);
//	set_history_mode(&g_minishell);
	signal_handling();
	while (1)
	{
		signal_handling();
		str = readline(PROMPT);
		if (!str)
			break ;
		add_history(str);
		lexer(str, &g_minishell.token);
		lexer_test(&g_minishell.token);
		clean_all(&g_minishell.token);
		free(str);
	}
}
