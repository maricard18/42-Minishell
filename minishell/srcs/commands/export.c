/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:35:27 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 12:46:13 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if env variable is valid
int	check_env_var(char *str)
{
	char	*equal_sign_ptr;

	equal_sign_ptr = ft_strchr(str, '=');
	if (!equal_sign_ptr || (equal_sign_ptr == str))
		return (0);
	while (*str)
	{
		if (is_whitespace(*str))
			return (0);
		str++;
	}
	return (1);
}

// add env variable to env array
void	add_env_var(char *str)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_calloc(sizeof(char *), number_args_env_var() + 2);
	while (g_minishell.ev[++i])
		new_env[i] = ft_strdup(g_minishell.ev[i]);
	new_env[i] = ft_strdup(str);
	free_array(g_minishell.ev);
	g_minishell.ev = new_env;
}

// check if env variable already exists
int	is_include(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (g_minishell.ev[i])
	{
		j = 0;
		while (g_minishell.ev[i][j] && str[j])
		{
			if (str[j] == '=' && g_minishell.ev[i][j] == '=')
				return (i);
			if (str[j] != g_minishell.ev[i][j])
				break ;
			j++;
		}
		i++;
	}
	return (-1);
}

void	export_print_all(void)
{
	int	i;

	i = 0;
	while (g_minishell.ev[i] != NULL)
	{
		printf("declare -x %s\n", g_minishell.ev[i]);
		i++;
	}
}

void	export_command(char **input)
{
	int	index;

	if (*++input == NULL)
	{
		sort_env_variables(g_minishell.ev);
		export_print_all();
		return ;
	}
	while (*input)
	{
		if (check_env_var(*input))
		{
			index = is_include(*input);
			if (index != -1)
				g_minishell.ev[index] = ft_strdup(*input);
			else
				add_env_var(*input);
		}
		input++;
	}
	sort_env_variables(g_minishell.ev);
	update_path_directories();
}
