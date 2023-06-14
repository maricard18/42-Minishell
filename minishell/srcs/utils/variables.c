/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:26:56 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 11:28:38 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// duplicate environment variable
char	**dup_env_var(char **ev)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (ev[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (0);
	i = -1;
	while (ev[++i])
		env_copy[i] = ft_strdup(ev[i]);
	env_copy[i] = 0;
	return (env_copy);
}

// init minishell variables
void	minishell_init(char **ev)
{
	errno = 0;
	g_minishell.ev = dup_env_var(ev);
	g_minishell.paths = ft_split(getenv("PATH"), ':');
	g_minishell.exit_status = 0;
	g_minishell.token = NULL;
	g_minishell.parsed = NULL;
	g_minishell.fd = NULL;
	g_minishell.exit_status = 0;
	g_minishell.error = 0;
}
