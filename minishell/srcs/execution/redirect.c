/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:20 by maricard          #+#    #+#             */
/*   Updated: 2023/06/03 11:13:39 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// here doc handler
void	here_doc(t_parsed *temp)
{
	char	*str;
	char	*keyword;

	keyword = temp->file->name;
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			printf("%s : not found\n", keyword);
			free(str);
			break ;
		}
		if (ft_strcmp(str, keyword) == 0)
		{
			free(str);
			break ;
		}
		free(str);
	}
}

// append handler
void	append(t_parsed *temp)
{
	int	file;
	int	fd;

	file = open(temp->file->name, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (file == -1)
	{
		perror("error opening file\n");
		exit(1);
	}
	fd = dup2(file, STDOUT_FILENO);
	if (fd == -1)
	{
		perror("error on dup2()\n");
		exit(1);
	}
	execve_or_builtin(temp->args);
	close(file);
}

// redirect_out handler
void	redirect_out(t_parsed *temp)
{
	int	file;
	int	fd;

	file = open(temp->file->name, O_RDONLY, 0777);
	if (file == -1)
	{
		perror("file does not exist\n");
		exit(1);
	}
	fd = dup2(file, STDIN_FILENO);
	if (fd == -1)
	{
		perror("error on dup2()\n");
		exit(1);
	}
	execve_or_builtin(temp->args);
	close(file);
}

// redirect_in handler
void	redirect_in(t_parsed *temp)
{
	int	file;
	int	fd;

	file = open(temp->file->name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file == -1)
	{
		perror("error opening file\n");
		exit(1);
	}
	fd = dup2(file, STDOUT_FILENO);
	if (fd == -1)
	{
		perror("error on dup2()\n");
		exit(1);
	}
	execve_or_builtin(temp->args);
	close(file);
}
