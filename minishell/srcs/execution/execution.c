/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:51:08 by maricard          #+#    #+#             */
/*   Updated: 2023/05/16 20:33:02 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

void    test_values()
{
	g_minishell.parsed = *(t_parsed *)malloc(sizeof(t_parsed));
	
	g_minishell.parsed.args = malloc(sizeof(char *) * 3);
	g_minishell.parsed.args[0] = ft_strdup("ls");
	g_minishell.parsed.args[1] = ft_strdup("-l");
	g_minishell.parsed.args[2] = NULL;


	g_minishell.parsed.next = malloc(sizeof(t_parsed));

	g_minishell.parsed.next->args = malloc(sizeof(char *) * 3);
	g_minishell.parsed.next->args[0] = ft_strdup("echo"); 
	g_minishell.parsed.next->args[1] = ft_strdup("ola");
	g_minishell.parsed.next->args[2] = NULL;


	g_minishell.parsed.file.type = STRING;
	g_minishell.parsed.file.name = "1";
	g_minishell.parsed.next = NULL;
}

void    execution()
{

// test_values();
//	execute_execve(g_minishell.parsed.args);
//	execute_builtin_command(g_minishell.parsed.args);
//	redirect_in();
//	redirect_out();
//	append();
//	here_doc(g_minishell.parsed.args[0]);
	pipe_handle();
	return ;
}