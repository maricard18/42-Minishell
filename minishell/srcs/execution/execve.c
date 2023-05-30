/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:35:27 by maricard          #+#    #+#             */
/*   Updated: 2023/05/30 18:35:32 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// runs trough the string until it finds a delimeter
char	*ft_strtok(char *str, char delimeter)
{
	int			i;
	static char	*old_str;
	char		*new_str;

	if (str != NULL)
		old_str = str;
	if (old_str == NULL)
		return (NULL);
	i = 0;
	while (1)
	{
		if (old_str[i] == delimeter)
		{
			new_str = ft_substr(old_str, 0, i);
			old_str = ft_strchr(old_str, delimeter) + 1;
			return (new_str);
		}
		else if (old_str[i] == '\0')
		{
			new_str = ft_substr(old_str, 0, i);
			old_str = NULL;
			return (new_str);
		}
		i++;
	}
}

// search command path
char	*search_path(char *arg)
{
	char	*full_path;
	char	*command;
	char	*path;
	char	*tok;

	command = ft_strjoin("/", arg);
	path = getenv("PATH");
	tok = ft_strtok(path, ':');
	while (tok != NULL)
	{
		full_path = ft_strjoin(tok, command);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		else
		{
			free(full_path);
			tok = ft_strtok(NULL, ':');
		}
	}
	perror("minishell: command not found\n");
	return (NULL);
}

// execve handler
void	execute_execve(char **args)
{
	int		pid;
	int		status;
	char	*full_path;

	full_path = search_path(args[0]);
	if (full_path == NULL)
		return ;
	pid = fork();
	if (pid == 0)
		execve(full_path, args, NULL);
	else
		waitpid(pid, &status, 0);
	return ;
}
