/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:01:01 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 12:02:31 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// pipe checker
int	check_for_pipes(char *str, t_token *temp)
{
	if (ft_strchr(str, '|') != 0)
	{
		temp->type = PIPE;
		return (1);
	}
	else
		return (0);
}

// redirect_in checker
int	check_for_redirect_in(char *str, t_token *temp)
{
	if (ft_strchr2(str, '>') == 2)
	{
		temp->type = APPEND;
		return (1);
	}
	else if (ft_strchr2(str, '>') == 1)
	{	
		temp->type = GREATER;
		return (1);
	}
	else
		return (0);
}

// redirect_out checker
int	check_for_redirect_out(char *str, t_token *temp)
{
	if (ft_strchr2(str, '<') == 2)
	{
		temp->type = HERE_DOC;
		return (1);
	}
	else if (ft_strchr2(str, '<') == 1)
	{
		temp->type = SMALLER;
		return (1);
	}
	else
		return (0);
}
