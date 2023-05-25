/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:00:53 by filipa            #+#    #+#             */
/*   Updated: 2023/05/25 14:25:42 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_state g_minishell;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*str;

	minishell_init(envp);
	while (1)
	{
		signal(SIGINT, &ctrl_c);
        signal(SIGQUIT, SIG_IGN);
		str = readline(PROMPT);
		ctrl_d(str);
		initialize_shell(str);
		clean_all(str);
	}
	return(0);
}
