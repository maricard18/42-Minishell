/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:26:56 by maricard          #+#    #+#             */
/*   Updated: 2023/05/11 12:11:32 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (++i);
}

char	**env_dup(char **env)
{
	char	**env_array;
	int		i;

	i = 0;
	env_array = malloc(sizeof(char *) * env_size(env));
	if (!env_array)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		env_array[i] = ft_strdup(env[i]);
		i++;
	}
	env_array[i] = 0;
	return (env_array);
}


void	minishell_init(t_minishell_state *shell, char **env)
{
	shell->status = 0;
	shell->status_signal = 0;
	shell->input = NULL;
	shell->environment_variables = env_dup(env);
	if (!shell->environment_variables)
		exit(EXIT_FAILURE);
	shell->pwd = getcwd(NULL, 0); //retorna o diretório de trabalho atual em forma de uma string de caracteres.
	shell->fd_in = 0;
	shell->fd_out = 1;
	shell->any_redirection = 1;
	shell->history_head = NULL;
	shell->history_index = NULL;
}
