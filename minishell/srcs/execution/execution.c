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
    g_minishell.parser.args = malloc(sizeof(char *) * 3);
    g_minishell.parser.args[0] = malloc(sizeof(char) * 3);
    g_minishell.parser.args[0] = ft_strdup("ls");
   g_minishell.parser.args[1] = malloc(sizeof(char) * 3);
   g_minishell.parser.args[1] = ft_strdup("-l")  ; 
    g_minishell.parser.args[2] = NULL;
    
    g_minishell.parser.flag = 0;
    
    g_minishell.parser.file.type = STRING;
    
    g_minishell.parser.next = NULL;
}

void    execution()
{
    g_minishell.parser = *(t_parser *)malloc(sizeof(t_parser));
    test_values();
    check_files();
    // if ((g_minishell.parser.file.type == STRING) && (g_minishell.parser.flag == 0))
    //     execute_execve(g_minishell.parser.args);
    // if ((g_minishell.parser.file.type == STRING) && (g_minishell.parser.flag == 1))
    //     execute_builtin_command(g_minishell.parser.args);
    return ;
}