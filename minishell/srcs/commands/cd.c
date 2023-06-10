/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:35:35 by maricard          #+#    #+#             */
/*   Updated: 2023/06/10 17:35:36 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd handler
void	cd_command(char **input)
{
	if (input[1])
	{
		if (chdir(input[1]))
			perror("Failed to change directory");
	}
	else if (chdir(getenv("HOME")))
		perror("Home directory not found");
}
