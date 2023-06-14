/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:00:11 by mariohenriq       #+#    #+#             */
/*   Updated: 2023/06/14 15:42:32 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// print env variable
char	*env_var(char *env, int i)
{
	char	*str;
	int		a;
	int		k;

	i++;
	a = i;
	k = 0;
	while (env[a])
	{
		k++;
		a++;
	}
	str = malloc((k + 1) * sizeof(char));
	k = 0;
	while (env[i])
	{
		str[k] = env[i];
		k++;
		i++;
	}
	str[k] = '\0';
	return (str);
}

// check if $? was enetered
char	*check_if_exit_status(char *str, int *i)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_minishell.exit_status));
	}
	else if (str[*i] == '\0')
	{
		*i = ft_strlen(str);
		return (ft_strdup("$"));
	}
	else
	{
		if (str[*i] == '"' || str[*i] == '\'' || str[*i] == ' ')
		{
			return (ft_strdup("$"));
		}
		else
		{
			while (ft_isalnum(str[*i]) == 1)
				(*i)++;
			return (ft_strdup(""));
		}
	}
}

// handle env variables
char	*handle_env_variables(char **env, char *str, int *i)
{
	char	*new_str;
	int		j;
	int		a;
	int		k;

	j = -1;
	while (env[++j])
	{
		k = *i;
		a = 0;
		while (str[k] == env[j][a])
		{
			if (ft_isalnum(str[k + 1]) == 0 && env[j][a + 1] == '=')
			{
				*i = k + 1;
				return (env_var(env[j], a + 1));
			}
			a++;
			k++;
		}
	}
	new_str = check_if_exit_status(str, i);
	return (new_str);
}

// check what is inside the quotes or not
char	*check_string(char *str, int *a)
{
	char	**env;
	char	*new_str;

	env = g_minishell.ev;
	if (str[*a] == '$')
	{
		(*a)++;
		return (handle_env_variables(env, str, a));
	}
	else if (str[*a] == '"')
		return (double_quotes(env, str, a));
	else if (str[*a] == '\'')
		return (single_quotes(str, a));
	else
	{
		new_str = ft_char_string(str[*a]);
		(*a)++;
		return (new_str);
	}
}

// search for env variables
void	search_env_vars(char **str)
{
	char	*new_str;
	char	*temp;
	char	*check_str;
	int		i;
	int		a;

	i = 0;
	while (str[i])
	{
		a = 0;
		temp = ft_calloc(1, sizeof(char));
		while (str[i][a])
		{
			check_str = check_string(str[i], &a);
			new_str = ft_strjoin(temp, check_str);
			temp = ft_strdup(new_str);
			free(check_str);
			free(new_str);
		}
		modify_string(&str[i], &temp);
		i++;
		if (ft_strcmp(str[i - 1], "<<") == 0 && str[i] != NULL)
			i++;
	}
	g_minishell.input = str;
}
