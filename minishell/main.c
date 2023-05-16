/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:00:53 by filipa            #+#    #+#             */
/*   Updated: 2023/05/16 09:55:42 by maricard         ###   ########.fr       */
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
		g_minishell.ignore = 0;//ignorar tudo
		signal(SIGINT, &ctrl_c);// quando crtl+c for pressionado aciona a nossa funcao
        signal(SIGQUIT, SIG_IGN);//Ctrl+C ser ignorado
		str = readline(PROMPT);
		ctrl_d(str);//Ctrl+D, imprime "exit" e sai, como um shell real.
		if (g_minishell.ignore)
        {
            free(str);
            str = malloc(1);//Ctrl+C, liberta memória usada e substitui por uma string vazia, só com o \0
        }
		if (*str)
		{
			lexer(str, &g_minishell.token);
			execute_builtin_command(g_minishell.token.args);
//			lexer_test(&g_minishell.token);
			clean_all(&g_minishell.token);
			add_history(str);
		}
		free(str);
	}
	return(0);
}
