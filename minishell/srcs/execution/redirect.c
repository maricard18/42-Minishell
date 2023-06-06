/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:20 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 14:33:06 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_here_doc(t_parsed *temp, char *keyword)
{
	char	*str;

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
	int	pipe_fd[2];

	pipe(pipe_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	exec_here_doc(temp, keyword);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	execve_or_builtin(temp->args);
	close(pipe_fd[0]);
}

// append handler
void	append(t_parsed *temp, t_file *file)
{
	int	file_fd;
	int	fd;

	file_fd = open(file->name, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (file_fd == -1)
	{
		perror("error opening file\n");
		exit(1);
	}
	if (file->next == NULL)
	{
		fd = dup2(file_fd, STDOUT_FILENO);
		if (fd == -1)
		{
			perror("error on dup2()\n");
			exit(1);
		}
		execve_or_builtin(temp->args);
	}
	close(file_fd);
}

// redirect_out handler
void	redirect_out(t_parsed *temp, t_file *file)
{
	int	file_fd;
	int	fd;

	file_fd = open(file->name, O_RDONLY, 0777);
	if (file_fd == -1)
	{
		perror("file does not exist\n");
		exit(1);
	}
	if (file->next == NULL)
	{
		fd = dup2(file_fd, STDIN_FILENO);
		if (fd == -1)
		{
			perror("error on dup2()\n");
			exit(1);
		}
		execve_or_builtin(temp->args);
	}
	close(file_fd);
}

// redirect_in handler
void	redirect_in(t_parsed *temp, t_file *file)
{
	int	file_fd;
	int	fd;

	file_fd = open(file->name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file_fd == -1)
	{
		perror("error opening file\n");
		exit(1);
	}
	if (file->next == NULL)
	{
		fd = dup2(file_fd, STDOUT_FILENO);
		if (fd == -1)
		{
			perror("error on dup2()\n");
			exit(1);
		}
		execve_or_builtin(temp->args);
	}
	close(file_fd);
}
