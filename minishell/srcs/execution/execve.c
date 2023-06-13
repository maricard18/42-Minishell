/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:35:27 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 21:14:00 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

void	execute(char *full_path, char **args)
{
	if (g_minishell.flag2 == 0)
	{
		execve(full_path, args, g_minishell.ev);
		print_error(args[0], ": Permission denied\n", 126);
		exit(126);
	}
	else
		exit(1);
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
	print_error(arg, ": command not found\n", 127);
	return (NULL);
}

// execve handler
void	execute_execve(char **args)
{
	char	*full_path;
	char	*path;

	full_path = NULL;
	path = my_get_env(g_minishell.ev, "PATH");
	if (path == NULL)
	{
		print_error(args[0], ": No such file or directory\n", 127);
		exit(g_minishell.exit_status);
	}
	if (check_if_path(args[0]) == 0)
	{
		full_path = search_path(args[0], path);
		if (full_path == NULL)
		{
			free(path);
			exit(g_minishell.exit_status);
		}
		else
			execute(full_path, args);
		free(full_path);
	}
	else
		execute(args[0], args);
	free(path);
}
