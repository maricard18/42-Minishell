/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:09:49 by maricard          #+#    #+#             */
/*   Updated: 2023/05/25 14:10:34 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// validate syntax
int validate_syntax(t_token *my_tokens) 
{
    t_token *tmp_tokens = my_tokens;
    int paranthesis_count = 0;

    while (tmp_tokens) 
    {
        if (tmp_tokens->type == PIPE
            || tmp_tokens->type == AND
            || tmp_tokens->type == OR
            || tmp_tokens->type == CLOSE_PAR) 
        {
            if (!tmp_tokens->prev
                || tmp_tokens->prev->type == OPEN_PAR
                || tmp_tokens->prev->type == PIPE
                || tmp_tokens->prev->type == AND
                || tmp_tokens->prev->type == OR) 
            {
                return (handle_error(SYNTAX_ERROR, tmp_tokens->value));
            }
            else if (tmp_tokens->type != CLOSE_PAR && !tmp_tokens->next)
                return (handle_error(SYNTAX_ERROR, "Incomplete command after operator"));
        }
        if (tmp_tokens->type == SMALLER
            || tmp_tokens->type == GREATER
            || tmp_tokens->type == HERE_DOC
            || tmp_tokens->type == APPEND) 
        {
            if (!tmp_tokens->next)
                return (handle_error(SYNTAX_ERROR, "Unexpected newline after redirection symbol"));
            else if (tmp_tokens->next->type != STRING)
                return (handle_error(SYNTAX_ERROR, tmp_tokens->next->value));
        }
        else if (tmp_tokens->type == OPEN_PAR)
        {
            if (tmp_tokens->prev && tmp_tokens->prev->type == STRING)
                return (handle_error(SYNTAX_ERROR, tmp_tokens->value));
            paranthesis_count++;
        }
        else if (tmp_tokens->type == CLOSE_PAR) {
            if (tmp_tokens->next && tmp_tokens->next->type == STRING) {
                return (handle_error(SYNTAX_ERROR, tmp_tokens->next->value));
            }
            paranthesis_count--;
        }
        if (!tmp_tokens->next && paranthesis_count > 0)
            return (handle_error(SYNTAX_ERROR, "Unclosed parenthesis"));
        tmp_tokens = tmp_tokens->next;
    }

    return (0);
}
