/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:36:29 by maricard          #+#    #+#             */
/*   Updated: 2023/05/16 18:48:30 by maricard         ###   ########.fr       */
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
