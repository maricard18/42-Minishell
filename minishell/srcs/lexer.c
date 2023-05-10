/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:11:53 by maricard          #+#    #+#             */
/*   Updated: 2023/05/10 11:01:30 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

int     skip_quotes(char *str, int i)
{
    char    quote;

    quote = str[i];
    i++;
    while (str[i] && str[i] != quote)
        i++;
    if (str[i] == quote)
        i++;
    return (i);
}

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
            while (str[i] && str[i] != ' ')
            {
                if (str[i] == '\'' || str[i] == '"')
                    i = skip_quotes(str, i);
                else
                    i++;
            }
            token->args[token->index] = ft_substr(str, a, i - a);
        }
        if (str[i] == '\0')
            break ;
        else
            token->index++;
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
        while (str[i] && str[i] == ' ')
           i++;
        if (str[i] && str[i] != ' ')
        {
            while (str[i] && str[i] != ' ')
            {
                if (str[i] == '\'' || str[i] == '"')
                    i = skip_quotes(str, i);
                else
                    i++;
            }
            tokens++;
        }
        if (str[i] == '\0')
            break ;
    }
    return (tokens);
}

void    lexer(char *str, t_token *token)
{
    token->n_tokens = count_tokens(str);
    token->args = malloc(sizeof(char *) * (token->n_tokens + 1));
    if (!token->args)
        exit(1);
    token->args[token->n_tokens + 1] = NULL;
    token->index = 0;
    store_tokens(str, token);
}
