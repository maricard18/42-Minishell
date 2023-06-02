/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:00:11 by mariohenriq       #+#    #+#             */
/*   Updated: 2023/06/02 23:09:52 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	str = ft_calloc(k + 1, sizeof(char));
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

// handle env variables
char	*handle_env_variables(char **env, char *str, int *i)
{
	char	*new_str;
	int		j;
	int		a;
	int		k;

	j = 0;
	while (env[j])
	{
		k = *i;
		a = 0;
		while (str[k] == env[j][a])
		{
			if (ft_isalnum(str[k + 1]) == 0 || env[j][a + 1] == '=') // ! bad condition
			{
				*i = k + 1;
				return (env_var(env[j], a + 1));
			}
			a++;
			k++;
		}
		j++;
	}
	new_str = ft_strdup("");
	*i = ft_strlen(str);
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
	{
		return (double_quotes(env, str, a));
	}
	else if (str[*a] == '\'')
	{
		return (single_quotes(str, a));
	}
	else
	{
		new_str = ft_char_string(str[*a]);
		(*a)++;
		return (new_str);
	}
}
// ! not handled $ not existing
// search for env variables
void	search_env_vars(void)
{
	char	*new_str;
	char	*temp;
	char	**str;
	int		i;
	int		a;

	str = g_minishell.input;
	i = 0;
	while (str[i])
	{
		a = 0;
		temp = ft_calloc(1, sizeof(char));
		while (str[i][a])
		{
			new_str = ft_strjoin(temp, check_string(str[i], &a));
			temp = ft_strdup(new_str);
			free(new_str);
		}
		modify_string(&str[i], temp);
		free(temp);
		i++;
	}
	g_minishell.input = str;
}
