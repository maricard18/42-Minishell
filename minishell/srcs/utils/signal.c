/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:36:29 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 11:47:44 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// handle ctrl^C
void    ctrl_c(int signal)
{
    (void)signal;
	
	ft_putchar_fd('\n', STDOUT_FILENO);		// Print a newline
	rl_on_new_line(); 						// Go to a new line
	rl_replace_line("", 0);  				// Replace the current line with an empty line
	rl_redisplay();  						// Redisplay the prompt
	g_minishell.exit_status = 130;
}

// handle ctrl^D
void    ctrl_d(char *str)
{
    if (!str)
    {
        printf("exit\n");
		free(str);
		exit(errno);
    }
}
