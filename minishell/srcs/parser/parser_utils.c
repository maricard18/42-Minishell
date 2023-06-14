/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:37:25 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 13:40:38 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// alocate and initialize command
t_parsed	*init_command(int in_file, int out_file)
{
	t_parsed	*command;

	command = (t_parsed *)malloc(sizeof(t_parsed));
	command->exec = 0;
	command->in_file = in_file;
	command->out_file = out_file;
	command->cmd = ft_calloc(2, sizeof(char));
	command->prev = NULL;
	command->next = NULL;
	command->file = NULL;
	command->args = ft_calloc(2, sizeof(char *));
	return (command);
}

// create a new array in case of pipe
void	add_cmd_to_list(t_parsed *current_command, t_parsed **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	list[i] = current_command;
	list[i + 1] = NULL;
}
