/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:36:29 by maricard          #+#    #+#             */
/*   Updated: 2023/05/10 11:12:58 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
//  exit(0);
}

// control ^\ handler
void    sigquit_handler(int signal)
{
    (void)signal;
    printf("control ^\\ pressed\n");
}

// signal handling
void    signal_handling(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGQUIT, sigquit_handler);
}