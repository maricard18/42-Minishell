/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:35:35 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 21:57:52 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd handler
void	cd_command(char **input)
{
	if (input[1])
	{
		if (input[2])
		{
			print_error(NULL, "error: too many arguments.\n", 1);
			return ;
		}
		else if (chdir(input[1]))
		{
			print_error(NULL, "error: failed to change directory.\n", 1);
			return ;
		}
		g_minishell.exit_status = 0;
	}
	else
	{
		if (chdir(getenv("HOME")) == 0)
			g_minishell.exit_status = 0;
		else
			print_error(NULL, "error: Home directory not found.\n", 1);
	}
}
