/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:35:48 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 19:39:56 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// remove env var
void	remove_env_var(char *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(sizeof(char *), number_args_env_var() + 1);
	while (g_minishell.ev[i])
	{
		if (ft_strncmp(g_minishell.ev[i], data, ft_strlen(data)))
		{
			new_env[j] = ft_strdup(g_minishell.ev[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_array(g_minishell.ev);
	g_minishell.ev = new_env;
}

// remove env vars
void	unset_command(char **input)
{
	char	*data;

	input++;
	while (*input)
	{
		data = ft_strjoin2(*input, "=");
		remove_env_var(data);
		free(data);
		input++;
	}
	update_path_directories();
	g_minishell.exit_status = 0;
}
