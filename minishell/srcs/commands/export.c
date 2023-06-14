/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:35:27 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 15:59:06 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// error handling for export
int	check_env_var(char *str, int *error)
{
	if (ft_isdigit(*str))
	{
		if (*error == 0)
			print_error(NULL, "error: export bad syntax\n", 1);
		return (0);
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

// print "declare -x" for all env variables
void	export_print_all(void)
{
	int	i;
	int	a;

	i = 0;
	while (g_minishell.ev[i] != NULL)
	{
		a = 0;
		printf("declare -x ");
		while (g_minishell.ev[i][a] != '=' && g_minishell.ev[i][0])
		{
			printf("%c", g_minishell.ev[i][a]);
			a++;
		}
		printf("%c", g_minishell.ev[i][a]);
		printf("\"");
		a++;
		while (g_minishell.ev[i][a])
		{
			printf("%c", g_minishell.ev[i][a]);
			a++;
		}
		printf("\"\n");
		i++;
	}
}

// export handler
void	export_command(char **input)
{
	int	tmp;

	g_minishell.exit_status = 0;
	if (input[1] == NULL)
	{
		sort_and_print();
		return ;
	}
	while (*++input)
	{
		if (check_for_equal_sign(*input, &g_minishell.error) == 0)
			continue ;
		if (*input && check_env_var(*input, &g_minishell.error))
		{
			if (is_include(*input) != -1)
			{
				tmp = is_include(*input);
				free(g_minishell.ev[tmp]);
				g_minishell.ev[tmp] = ft_strdup(*input);
			}
			else
				add_env_var(*input);
		}
	}
	update_path_directories();
}
