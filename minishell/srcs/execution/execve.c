/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:35:27 by maricard          #+#    #+#             */
/*   Updated: 2023/05/17 15:13:34 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_strtok(char *str, char delimeter)
{
    int         i;
    static char *old_str;
    char        *new_str;

    if (str != NULL)
        old_str = str;
    if (old_str == NULL)
        return (NULL);
    i = 0;
    while (1)
    {
        if (old_str[i] == delimeter)
        {
            new_str = ft_substr(old_str, 0, i);
            old_str = ft_strchr(old_str, delimeter) + 1;
            return (new_str);
        }
        else if (old_str[i] == '\0')
        {
            new_str = ft_substr(old_str, 0, i);
            old_str = NULL;
            return (new_str);   
        }
        i++;
    }
}

void    execute_execve(char **args)
{
    int i;
    (void)args;
    printf("\n"G"[ Entered execve function ]"RT"\n\n");
    char *str;
    char *tok;
    
    i = 0;
    str = getenv("PATH");
    tok = ft_strtok(str, ':');
    while (tok != NULL)
    {
        tok = ft_strtok(NULL, ':');
        i++;
    }
}