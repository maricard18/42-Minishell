/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipa <filipa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:00:53 by filipa            #+#    #+#             */
/*   Updated: 2023/05/10 20:17:36 by filipa           ###   ########.fr       */
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
	initialize_history(&g_minishell);
	set_history_mode(&g_minishell);
	signal_handling();
	while (1)
	{
		signal_handling();
		str = readline(PROMPT);
		if (!str)
			break ;
		lexer(str, &g_minishell.token);
		lexer_test(&g_minishell.token);
//		clean_all(&g_minishell->token);
	}
}
