/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:20 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 13:30:54 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_here_doc(t_parsed *temp, char *keyword)
{
	char *str;

	(void)temp;
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

// here doc handler
void	here_doc(t_parsed *temp, char *keyword)
{
	int		pipe_fd[2];

	pipe(pipe_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	exec_here_doc(temp, keyword);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	execve_or_builtin(temp->args);
	close(pipe_fd[0]);
}

// append handler
void	append(t_parsed *temp, char *name)
{
	int	file;
	int	fd;

	file = open(name, O_CREAT | O_WRONLY | O_APPEND, 0777);
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
void	redirect_out(t_parsed *temp, char *name)
{
	int	file;
	int	fd;

	file = open(name, O_RDONLY, 0777);
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
void	redirect_in(t_parsed *temp, char *name)
{
	int	file;
	int	fd;

	file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
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
