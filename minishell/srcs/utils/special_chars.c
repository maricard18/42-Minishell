/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:01:01 by maricard          #+#    #+#             */
/*   Updated: 2023/05/16 15:31:00 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// pipe checker
void    check_for_pipes(char *str)
{
    if (ft_strchr2(str, '|') == 1)
        g_minishell.token.type = PIPE;
    else if (ft_strchr2(str, '|') == 2)
        g_minishell.token.type = OR;
    else
        return ;
}

// redirect in checker
void    check_for_redirect_in(char *str)
{
    if (ft_strchr2(str, '>') == 1)
        g_minishell.token.type = GREATER;
    else if (ft_strchr2(str, '>') == 2)
        g_minishell.token.type = APPEND;
    else
        return ;
}

// redirect out checker
void    check_for_redirect_out(char *str)
{
    if (ft_strchr2(str, '<') == 1)
        g_minishell.token.type = SMALLER;
    else if (ft_strchr2(str, '<') == 2)
        g_minishell.token.type = HERE_DOC;
    else
        return ;
}
