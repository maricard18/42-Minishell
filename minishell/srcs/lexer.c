/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:11:53 by maricard          #+#    #+#             */
/*   Updated: 2023/05/07 01:09:31 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    token_division(char *str, t_token *token)
{
    int i;

    i = 0;
    (void)token;
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        // continuacao
    }
}

int    count_tokens(char *str)
{
    int i;
    int tokens;

    i = 0;
    tokens = 0;
    while (str[i])
    {
        if (str[i] == ' ')
        {
            while (str[i] == ' ')
                i++;
        tokens++;
        }
        i++;
    }
    return (tokens);
}

void    lexer(char *str, t_token *token)
{
    int i;

    (void)token;
    i = count_tokens(str);
//     if (i > 1)
//         token->str = malloc(sizeof(char *) * (i - 1) + 1);
//    token_division(str, token);
}