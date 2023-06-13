/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:35:54 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 19:27:59 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pwd handler
void	pwd_command(void)
{
	char	*current_dir;

	current_dir = getcwd(0, 0);
	if (!current_dir)
		print_error(NULL, "error: no such file or directory.\n", 127);
	else
	{
		g_minishell.exit_status = 0;
		printf("%s\n", current_dir);
	}
	free(current_dir);
}
