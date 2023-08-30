/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:20:29 by maricard          #+#    #+#             */
/*   Updated: 2023/06/16 15:25:02 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// duplicate the mains file descriptors
void	duplicate_fds(t_parsed *temp)
{
	if (temp->args[0])
	{
		temp->in_file = dup(g_minishell.in);
		temp->out_file = dup(g_minishell.out);
	}
	g_minishell.in = dup(STDIN_FILENO);
	g_minishell.in2 = dup(STDIN_FILENO);
	g_minishell.out = dup(STDOUT_FILENO);
	g_minishell.out2 = dup(STDOUT_FILENO);
}

// strlen until quote
int	ft_strlen_special(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '"' && str[i] != '\'' && str[i] != ' ')
		i++;
	return (i);
}

// print env variable
char	*my_get_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (env_var(env[i], ft_strlen(str)));
		i++;
	}
	return (NULL);
}

// check if the first arg is a path
int	check_if_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
