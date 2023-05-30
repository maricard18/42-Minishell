/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:09:10 by maricard          #+#    #+#             */
/*   Updated: 2023/05/30 18:30:29 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// copy string
char *ft_strcpy(char *dest, const char *src)
{
    int i = 0;
    
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int	token_counter(char **str)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i][0] == '|')
			a++;
		i++;
	}
	return (i - a);
}

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