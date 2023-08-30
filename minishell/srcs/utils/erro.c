/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:39:14 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 13:07:53 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// print to stdout error if error
void	print_error(char *arg, char *message, int exit_status)
{
	char	*str;

	str = ft_strjoin2(arg, message);
	ft_putstr_fd(str, 2);
	free(str);
	g_minishell.exit_status = exit_status;
}
