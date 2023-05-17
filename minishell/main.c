/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:00:53 by filipa            #+#    #+#             */
/*   Updated: 2023/05/17 11:16:33 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_minishell_state g_minishell;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*str;

	minishell_init(envp);
	while (1)
	{
//		g_minishell.ignore = 0;//ignorar tudo
		signal(SIGINT, &ctrl_c);
        signal(SIGQUIT, SIG_IGN);
		str = readline(PROMPT);
		ctrl_d(str);
//		if (g_minishell.ignore)
//		{
//          free(str);
//          str = malloc(1);//Ctrl+C, liberta memória usada e substitui por uma string vazia, só com o \0
//      }
//		if (*str)
//		{
			lexer(str);
//			execute_builtin_command(g_minishell.token.args);
			tokeniser(&g_minishell.token);
//			lexer_test();
			add_history(str);
			execution();
			clean_all(str);
//		}
	}
	return(0);
}
