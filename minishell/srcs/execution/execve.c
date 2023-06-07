/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:35:27 by maricard          #+#    #+#             */
/*   Updated: 2023/06/07 12:43:35 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
}

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
char	*search_path(char *arg, char *path)
{
	char	*full_path;
	char	*command;
	char	*tok;

	command = ft_strjoin2("/", arg);
	tok = ft_strtok(path, ':');
	while (tok != NULL)
	{
		full_path = ft_strjoin(tok, command);
		if (access(full_path, F_OK) == 0)
		{
			free(command);
			return (full_path);
		}
		else
		{
			free(full_path);
			tok = ft_strtok(NULL, ':');
		}
	}
	free(command);
	printf("%s : command not found\n", arg);
	g_minishell.exit_status = 127;
	return (NULL);
}

// execve handler
void	execute_execve(char **args)
{
	int		pid;
	char	*full_path;
	char	*path;

	path = getenv("PATH");
	if (args[0][0] != '/')
		full_path = search_path(args[0], path);
	else
		full_path = args[0];
	if (full_path == NULL)
		return ;
	signal(SIGINT, sigint_handler);
	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, g_minishell.ev);
		exit(126);
	}
	return ;
}
