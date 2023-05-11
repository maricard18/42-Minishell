/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:36:29 by maricard          #+#    #+#             */
/*   Updated: 2023/05/11 14:42:19 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// control ^C handler
void    sigint_handler(int signal)
{
    (void)signal;
    printf(" control ^C pressed\n");
}

// control ^D handler
void    sigterm_handler(int signal)
{
    (void)signal;
    printf("control ^D pressed\n");
}

// control ^\ handler
void    sigquit_handler(int signal)
{
    (void)signal;
    printf("control ^\\ pressed\n");
}

// signal handling
void    signal_handling()
{
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGQUIT, SIG_IGN);
}
