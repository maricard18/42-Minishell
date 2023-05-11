/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:50:03 by maricard          #+#    #+#             */
/*   Updated: 2023/05/11 10:24:15 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// skip quotes in input string
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

// return token index to store in args array
int     store_values2(char *str, int i)
{
    while (str[i] && str[i] != ' ')
    {
        if (str[i] == '\'' || str[i] == '"')
            i = skip_quotes(str, i);
        else if (str[i] == '|')
            return (i);
        else if (str[i] == '>' || str[i] == '<')
        {
            if (str[i + 1] == '>' || str[i + 1] == '<')
            {
                i++;
                return (i);
            }
            else
                return (i);
        }
        else if (str[i + 1] == '|')
            return (i);
        else if (str[i + 1] == '<' || str[i + 1] == '>')
            return (i);
        else
            i++;
    }
    return (i - 1);
}

// return next token index to count tokens
int     count_tokens2(char *str, int i)
{
    while (str[i] && str[i] != ' ')
    {
        if (str[i] == '\'' || str[i] == '"')
            i = skip_quotes(str, i);
        else if (str[i] == '|')
            return (++i);
        else if (str[i] == '>' || str[i] == '<')
        {
            if (str[i + 1] == '>' || str[i + 1] == '<')
            {
                i++;
                return (++i);
            }
            else
                return (++i);
        }
        else if (str[i + 1] == '|')
            return (++i);
        else if (str[i + 1] == '<' || str[i + 1] == '>')
            return (++i);
        else
            i++;
    }
    return (i);
}
