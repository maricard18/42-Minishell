/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:36:29 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 11:32:35 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// handle ctrl^C
void	ctrl_c(int signal)
{
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
	g_minishell.exit_status = 128 + signal;
}

// handle ctrl^D
void	ctrl_d(char *str)
{
	if (!str)
	{
		printf("exit\n");
		clean_all(str);
		clean_the_mess();
		exit(g_minishell.exit_status);
	}
}

// signal handler inside execve
void	sigint_handler(int signum)
{
	printf("\n");
	g_minishell.exit_status = 128 + signum;
}
