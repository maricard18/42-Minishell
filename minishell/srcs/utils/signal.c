/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipa <filipa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:36:29 by maricard          #+#    #+#             */
/*   Updated: 2023/05/11 19:05:39 by filipa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

void    ctrl_c(int signal)
{
    (void)signal;
    g_minishell.ignore = 1;//salta a linha actual
    ioctl(STDIN_FILENO, TIOCSTI, "\n");// mete caracter nova linha no terminal
    write(1, "\033[A", 3);
}

void    ctrl_d(char *str)//saio do programa
{
    if (!str)
    {
        printf("exit\n");
        exit(errno);
    }
}
