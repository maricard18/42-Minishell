/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:20:29 by maricard          #+#    #+#             */
/*   Updated: 2023/06/10 19:15:22 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// print to stdout error if error
void	print_error(char *arg, char *message, int exit_status)
{
	char	*str;

	str = ft_strjoin2(arg, message);
	ft_putstr_fd(str, 2);
	free(str);
	g_minishell.exit_status = exit_status;
}