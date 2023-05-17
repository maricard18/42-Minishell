/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:57:46 by maricard          #+#    #+#             */
/*   Updated: 2023/05/17 10:15:02 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// check the special characters
void special_chars(char *str)
{
    check_for_pipes(str);
    check_for_redirect_in(str);
    check_for_redirect_out(str);
    check_for_and(str);
    check_for_parentheses(str);
    check_for_string(str);
}

// atribute values to the arguments
void    tokeniser(t_token *temp)
{
    int i;

    i = 0;
    g_minishell.token = *(t_token*)malloc(sizeof(t_token));
    while (g_minishell.input[i])
    {
        g_minishell.token.value = ft_strdup(g_minishell.input[i]);
        special_chars(g_minishell.input[i]);
        g_minishell.token.index = i;
        if (i == 0)
            temp = &g_minishell.token;
        if (g_minishell.input[i + 1])
        {
           g_minishell.token.next = malloc(sizeof(t_token));
           g_minishell.token = *g_minishell.token.next;
        }
        else
        {
            g_minishell.token.next = NULL;
            break ;
        }
        i++;
    }
    g_minishell.token = *temp;
}
