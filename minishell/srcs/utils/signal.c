/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:36:29 by maricard          #+#    #+#             */
/*   Updated: 2023/05/24 19:30:13 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// handle ctrl C
void    ctrl_c(int signal)
{
    (void)signal;
    g_minishell.ignore = 1;//salta a linha actual
    ioctl(STDIN_FILENO, TIOCSTI, "\n");// mete caracter nova linha no terminal
    write(1, "\033[A", 3);
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
