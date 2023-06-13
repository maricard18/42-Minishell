/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:10:44 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 20:33:46 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// signal handler for parent process
void	igonre_signals(void)
{
	signal(SIGINT, SIG_IGN);
}

// here doc signal handler
void	here_doc_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	g_minishell.exit_status = 130;
}

// handler for here doc
void	here_doc_handler(t_parsed *temp, t_file **file, t_fd **fd)
{
	int	pid;

	signal(SIGINT, here_doc_sigint);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		here_doc(temp, file, fd);
		exit(g_minishell.exit_status);
	}
	else
	{
		igonre_signals();
		waitpid(pid, &g_minishell.exit_status, 0);
		if (WIFEXITED(g_minishell.exit_status))
			g_minishell.exit_status = WEXITSTATUS(g_minishell.exit_status);
	}
	if (g_minishell.n_tokens2 > 1)
		signal(SIGINT, sigint_handler);
	else
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
}
