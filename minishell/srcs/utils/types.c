/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:01:01 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 14:35:03 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// pipe checker
void	check_for_pipes(char *str, t_token *temp)
{
	if (ft_strchr2(str, '|') == 1)
		temp->type = PIPE;
	else if (ft_strchr2(str, '|') == 2)
		temp->type = OR;
	else
		return ;
}

// redirect_in checker
void	check_for_redirect_in(char *str, t_token *temp)
{
	if (ft_strchr2(str, '>') == 1)
		temp->type = GREATER;
	else if (ft_strchr2(str, '>') == 2)
		temp->type = APPEND;
	else
		return ;
}

// redirect_out checker
void	check_for_redirect_out(char *str, t_token *temp)
{
	if (ft_strchr2(str, '<') == 1)
		temp->type = SMALLER;
	else if (ft_strchr2(str, '<') == 2)
		temp->type = HERE_DOC;
	else
		return ;
}
