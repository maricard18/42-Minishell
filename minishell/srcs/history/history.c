/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:07:12 by filipa            #+#    #+#             */
/*   Updated: 2023/05/11 12:26:50 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_command_to_history(t_history_node **hist_head, char *command)
{
	t_history_node	*new;

	new = NULL;
	if (*command)
	{
		if (((*hist_head) && ft_strcmp((*hist_head)->content, command)) \
				|| !(*hist_head))
			new = ft_lstnew_2(ft_strdup(command));
		if (new)
		{
			if (!(*hist_head))
				*hist_head = new;
			else
			{
				new->next = *hist_head;
				(*hist_head)->previous = new;
				*hist_head = new;
			}
		}
	}
}

void	get_history_commands(int fd, t_minishell_state *data)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = get_next_line(fd, &line);
	while (ret >= 0)
	{
		if (*line != '\0')
			add_command_to_history(&data->history_head, line);
		free(line);
		if (ret == 0)
			break ;
		ret = get_next_line(fd, &line);
	}
}

void	initialize_history(t_minishell_state *data)
{
	int		fd;

	fd = open(HIST_FILE, O_RDONLY | O_CREAT, 0666);
	if (fd >= 0)
	{
		get_history_commands(fd, data);
		close(fd);
	}
}

