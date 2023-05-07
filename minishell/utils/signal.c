/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:36:29 by maricard          #+#    #+#             */
/*   Updated: 2023/05/07 00:31:21 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sigint_handler(int signal)
{
    (void)signal;
    printf(" control ^C pressed\n");  
}

void    sigterm_handler(int signal)
{
    (void)signal;
    printf("control ^D pressed\n");
//  exit(0);
}

void    sigquit_handler(int signal)
{
    (void)signal;
    printf("control ^\\ pressed\n");
}

void    signal_handling(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGQUIT, sigquit_handler);
}