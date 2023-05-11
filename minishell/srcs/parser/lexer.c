/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:11:53 by maricard          #+#    #+#             */
/*   Updated: 2023/05/11 10:45:17 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// store tokens in args array
void    store_tokens(char *str, t_token *token)
{
    int i;
    int a;

    i = 0;
    while (token->index <= token->n_tokens)
    {
        while (str[i] && str[i] == ' ')
           i++;
        if (str[i] && str[i] != ' ')
        {
            a = i;
            i = store_values2(str, i);
            token->args[token->index] = ft_substr(str, a, (i - a) + 1);
        }
        if (str[i] == '\0')
            break ;
        else
        {
            token->index++;
            i++;
        }
    }
}
// count tokens in input string
int    count_tokens(char *str)
{
    int i;
    int tokens;

    i = 0;
    tokens = 0;
    while (str[i])
    {
        while (str[i] && str[i] == ' ')
           i++;
        if (str[i] && str[i] != ' ')
        {
            i = count_tokens2(str, i);
            tokens++;
        }
        if (str[i] == '\0')
            break ;
    }
    return (tokens);
}

// Function to devide input string into tokens
void    lexer(char *str, t_token *token)
{
    token->n_tokens = count_tokens(str);
    token->args = malloc(sizeof(char *) * (token->n_tokens + 1));
    if (!token->args)
        exit(1);
    token->args[token->n_tokens] = NULL;
    token->index = 0;
    store_tokens(str, token);
}
