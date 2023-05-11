/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:45:38 by maricard          #+#    #+#             */
/*   Updated: 2023/05/11 11:12:27 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// clean function for lexer
void    clean_all(t_token *token)
{
    int i;

    i = 0;
    while (i <= token->n_tokens)
    {
        free(token->args[i]);
        printf("freed token->args[%d]\n", i);
        i++;
    }
    free(token->args);
}