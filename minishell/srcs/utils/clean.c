/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:45:38 by maricard          #+#    #+#             */
/*   Updated: 2023/05/24 19:30:46 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// clean function for lexer and tokanizer
void    clean_all(char *str)
{
    int i;

    i = 0;
    free(str);
    while (i < g_minishell.n_tokens)
    {
        free(g_minishell.input[i]);
        i++;
    }
    free(g_minishell.input);
}