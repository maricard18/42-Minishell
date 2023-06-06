/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:16:59 by filipa            #+#    #+#             */
/*   Updated: 2023/06/06 14:31:20 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_previous_input(int fd, char **line, char **saved_data)
{
	if (fd < 0 || !line || !BUFFER_SIZE)
		return (-1);
	if (saved_data[fd])
	{
		*line = ft_strdup(saved_data[fd]);
		ft_bzero(saved_data[fd], ft_strlen(saved_data[fd]));
		free(saved_data[fd]);
		saved_data[fd] = NULL;
	}
	else
		*line = ft_strdup("");
	if (!*line)
		return (-1);
	return (0);
}

static int	free_and_exit(char *str)
{
	free(str);
	return (-1);
}

static int	handle_end_of_line(int fd, char **line, char **saved_data,
		char *end_of_current_line)
{
	if (**line == 0)
	{
		if (saved_data[fd])
			free(saved_data[fd]);
		return (0);
	}
	if (end_of_current_line != NULL)
	{
		saved_data[fd] = ft_strdup(end_of_current_line + 1);
		if (!saved_data[fd])
			return (free_and_exit(*line));
		ft_bzero(end_of_current_line, ft_strlen(end_of_current_line));
		if (*saved_data[fd] == 0)
		{
			free(saved_data[fd]);
			saved_data[fd] = NULL;
		}
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*saved_data[FD_SETSIZE];
	char		buffer[BUFFER_SIZE + 1];
	int			read_result;
	char		*new_line;

	read_result = get_previous_input(fd, line, saved_data);
	if (read_result == -1)
		return (-1);
	new_line = ft_strchr(*line, '\n');
	while (new_line == NULL)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		read_result = read(fd, buffer, BUFFER_SIZE);
		if (read_result < 0)
			return (free_and_exit(*line));
		if (read_result == 0)
			break ;
		new_line = *line;
		*line = ft_strjoin(*line, buffer);
		if (!*line)
			return (free_and_exit(new_line));
		free(new_line);
		new_line = ft_strchr(*line, '\n');
	}
	return (handle_end_of_line(fd, line, saved_data, new_line));
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

int	main(void)
{
    printf("FD_SETSIZE=%d\n", FD_SETSIZE);
    return (0);
}

*/