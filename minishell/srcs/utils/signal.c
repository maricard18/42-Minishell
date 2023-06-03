/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:36:29 by maricard          #+#    #+#             */
/*   Updated: 2023/06/03 12:27:22 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// handle ctrl C
void    ctrl_c(int signal)
{
    (void)signal;
    //g_minishell.ignore = 1;//salta a linha actual
    //ioctl(STDIN_FILENO, TIOCSTI, "\n");// mete caracter nova linha no terminal
    //write(1, "\033[A", 3);
	
	ft_putchar_fd('\n', STDOUT_FILENO);	// Print a newline
	rl_on_new_line(); 					// Go to a new line
	//rl_replace_line("", 0);  			// Replace the current line with an empty line
	rl_redisplay();  					// Redisplay the prompt
}

// handle ctrl D
void    ctrl_d(char *str)
{
    if (!str)
    {
        printf("exit\n");
		exit(errno);
    }
}
