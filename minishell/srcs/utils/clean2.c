/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:56:00 by maricard          #+#    #+#             */
/*   Updated: 2023/06/27 19:05:28 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//clean list fd
void	clean_fd_list(t_fd *fd)
{
	t_parsed	**temp;
	t_file		*file;
	t_fd		*tmp;
	int			i;

	i = -1;
	g_minishell.fd = fd;
	temp = g_minishell.parsed;
	while (temp[++i])
	{
		file = temp[i]->file;
		while (file)
		{
			tmp = fd->next;
			free(fd);
			fd = tmp;
			file = file->next;
		}
	}
	g_minishell.fd = NULL;
}

// clean all the stuff
void	clean_the_mess(void)
{
	int	i;

	i = 0;
	if (g_minishell.paths)
	{
		while (g_minishell.paths[i])
		{
			free(g_minishell.paths[i]);
			i++;
		}
		free(g_minishell.paths);
	}
	g_minishell.paths = NULL;
	i = 0;
	if (g_minishell.ev)
	{
		while (g_minishell.ev[i])
		{
			free(g_minishell.ev[i]);
			i++;
		}
		free(g_minishell.ev);
	}
	g_minishell.ev = NULL;
}
