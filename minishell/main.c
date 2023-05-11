/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipa <filipa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:00:53 by filipa            #+#    #+#             */
/*   Updated: 2023/05/11 17:41:55 by filipa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_minishell_state g_minishell;

void    ctrl_c(int signal)
{
    (void)signal;
    g_minishell.ignore = 1;//salta a linha actual
    ioctl(STDIN_FILENO, TIOCSTI, "\n");// mete caracter nova linha no terminal
    write(1, "\033[A", 3);
}

void    ctrl_d(char *str)
{
    if (!str)
    {
        printf("exit\n");
        exit(errno);
    }
}

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
			lexer_test(&g_minishell.token);
			clean_all(&g_minishell.token);
			add_history(str);
			printf("\n");
		}
		free(str);
	}
	return(0);
}
