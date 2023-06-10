/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:57 by maricard          #+#    #+#             */
/*   Updated: 2023/06/10 17:13:28 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// signal handler inside execve
void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
}

// write to pipe in here doc
void	write_here_doc(int pipe_fd, char *str)
{
	write(pipe_fd, str, ft_strlen(str));
	write(pipe_fd, "\n", 1);
}

// check if the next node is a here doc
int	check_next_node(t_file **file)
{
	if ((*file)->next == NULL || (*file)->next->type != HERE_DOC)
	{
		return (0);
	}
	else
	{
		*file = (*file)->next;
		return (1);
	}
}

// count the number of characters until the next character c
int	ft_strclen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}
