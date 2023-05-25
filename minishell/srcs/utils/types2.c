/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:01:01 by maricard          #+#    #+#             */
/*   Updated: 2023/05/16 12:20:03 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// () checker
void    check_for_parentheses(char *str, t_token *temp)
{
    if (ft_strchr3(str, '(', ')') == 1)
        temp->type = OPEN_PAR;
    else if (ft_strchr3(str, '(', ')') == 2)
        temp->type = CLOSE_PAR;
    else
        return ;
}

// string checker
void    check_for_string(char *str, t_token *temp)
{
    if (is_string(str) == 1)
        temp->type = STRING;
    else
        return ;
}

// && checker
void    check_for_and(char *str, t_token *temp)
{   
    if (ft_strchr2(str, '&') == 2)
        temp->type = AND;
    else
        return ;
}
