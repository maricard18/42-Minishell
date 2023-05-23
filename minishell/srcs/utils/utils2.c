/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:51:04 by maricard          #+#    #+#             */
/*   Updated: 2023/05/23 11:18:31 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_string(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|' || str[i] == '>' || str[i] == '<' ||
                str[i] == '(' || str[i] == ')' || str[i] == '&')
		{
			if (str[i] == '&' && str[i + 1] != '&')
				return (1);	
            return (0);
		}
        i++;
    }
    return (1);
}

int ft_strchr2(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
        {
            if (s[i + 1] == c)
                return (2);
			return (1);
        }
		i++;
	}
	return (0);
}

int ft_strchr3(const char *s, char c, char d)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
        else if (s[i] == d)
            return (2);
		i++;
	}
	return (0);
}

int ft_strchr4(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
        {
            if (s[i + 1] == c)
                return (2);
        }
		i++;
	}
	return (0);
}

// char *ft_strcpy(char *dest, const char *src)
// {
//     int i = 0;
    
//     while (src[i] != '\0')
//     {
//         dest[i] = src[i];
//         i++;
//     }
//     dest[i] = '\0';
    
//     return dest;
// }

// void get_next_token(t_token *command_table)
// {
//     t_token *tmp_command_table;
//     t_token *new_tokens;
//     char *input;

//     tmp_command_table = command_table;
//     while (tmp_command_table->next)
//         tmp_command_table = tmp_command_table->next;
//     input = readline("> ");
//     new_tokens = identificar_agrupar_tokens(input);
//     new_tokens->prev = tmp_command_table;
//     tmp_command_table->next = new_tokens;
// }