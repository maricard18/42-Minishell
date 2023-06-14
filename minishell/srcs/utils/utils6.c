/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:44:25 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 15:28:16 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// array checker  for quotes
int	check_for_quotes(int k, t_token *token)
{
	if (g_minishell.str2[k])
	{
		if (g_minishell.str2[k][0] == '"' || g_minishell.str2[k][0] == '\'')
		{
			token->type = STRING;
			return (1);
		}
	}
	return (0);
}	