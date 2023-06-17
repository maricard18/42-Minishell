/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:10:44 by maricard          #+#    #+#             */
/*   Updated: 2023/06/17 12:47:16 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if there is a next node
void	check_for_next_node(t_parsed *temp, t_file **file)
{
	if ((*file)->next != NULL)
	{
		*file = (*file)->next;
		return ;
	}
	else if (temp->args[0])
	{
		*file = (*file)->next;
		execve_or_builtin(temp->args);
	}
}

// create a string for here doc
char	*create_string(char *temp, char c)
{
	char	*char_str;
	char	*new_str;

	char_str = ft_char_string(c);
	new_str = ft_strjoin(temp, char_str);
	temp = ft_strdup(new_str);
	free(new_str);
	free(char_str);
	return (temp);
}

// function to handle env variables inside here doc
char	*search_expansions(char **env, char *str)
{
	char	*temp;
	char	*var;
	int		i;

	temp = ft_calloc(1, sizeof(char));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			i++;
			var = handle_env_variables(env, str, &i);
			temp = ft_strjoin(temp, var);
			free(var);
		}
		if (str[i] == '\0')
			break ;
		if (str[i] == '$')
			continue ;
		temp = create_string(temp, str[i]);
	}
	return (temp);
}
