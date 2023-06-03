/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:09:10 by maricard          #+#    #+#             */
/*   Updated: 2023/06/03 10:55:57 by maricard         ###   ########.fr       */
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

// token counter
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

// modify string
void	modify_string(char **str, char *new_str)
{
	free(*str);
    *str = ft_strdup(new_str);
}

// one char string
char	*ft_char_string(char c)
{
	char *str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

// join two strings without free
char	*ft_strjoin2(char const *s1, char const *s2)
{
	int		i;
	int		a;
	char	*str;

	if (!s1)
		return (0);
	i = ft_strlen(s1);
	a = ft_strlen(s2);
	str = malloc((a + i) * sizeof(char) + 1);
	if (!str)
		return (0);
	i = 0;
	a = 0;
	while (s1[i])
		str[a++] = s1[i++];
	i = 0;
	while (s2[i])
		str[a++] = s2[i++];
	str[a] = '\0';
	return (str);
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