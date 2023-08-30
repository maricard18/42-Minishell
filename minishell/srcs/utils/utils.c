/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:42:53 by filipa            #+#    #+#             */
/*   Updated: 2023/06/14 12:35:59 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// get the value of the environment variable
char	*get_env(char *var_name)
{
	int		i;
	int		j;
	char	*env_str;

	i = -1;
	j = 0;
	env_str = ft_strjoin2(var_name, "=");
	while (g_minishell.ev[++i])
	{
		if (!ft_strncmp(g_minishell.ev[i], env_str, ft_strlen(env_str)))
		{
			while (g_minishell.ev[i][j] != '=')
				j++;
			free(env_str);
			return (ft_strdup(&g_minishell.ev[i][j + 1]));
		}
	}
	free(env_str);
	return (ft_calloc(sizeof(char *), 1));
}

// update path directories
void	update_path_directories(void)
{
	char	*path;

	if (g_minishell.paths)
		free_array(g_minishell.paths);
	path = get_env("PATH");
	if (!(*path))
		g_minishell.paths = 0;
	else
		g_minishell.paths = ft_split(path, ':');
	free(path);
}

// counter of environment variables
int	number_args_env_var(void)
{
	int	i;

	i = -1;
	while (g_minishell.ev[++i])
		;
	return (i);
}

// free memory of array
void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

// check if the character is a whitespace
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}
