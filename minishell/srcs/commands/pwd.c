/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:35:54 by maricard          #+#    #+#             */
/*   Updated: 2023/06/10 17:37:13 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pwd handler
void	pwd_command(void)
{
	char	*current_dir;

	current_dir = getcwd(0, 0);
	if (!current_dir)
		perror("Error while getting the current directory.");
	else
		printf("%s\n", current_dir);
	free(current_dir);
}
