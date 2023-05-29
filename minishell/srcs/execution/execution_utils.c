/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:20:40 by maricard          #+#    #+#             */
/*   Updated: 2023/05/29 23:49:14 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if its a builtin command or not
void    execve_or_builtin(char **args)
{
    if (get_builtin_type(args[0]) != 0)
        execute_builtin_command(args);
    else
        execute_execve(args);
}

// handler for execution in pipes
void    execute_commands(t_parsed *temp)
{
    if (temp->file == NULL)
        execve_or_builtin(temp->args);
    else if (temp->file->type == GREATER)
        redirect_in(temp);
    else if (temp->file->type == SMALLER)
        redirect_out(temp);
    else if (temp->file->type == APPEND)
        append(temp);
    else if (temp->file->type == HERE_DOC)
        here_doc(temp);
    else
    {
        printf("error\n");
        exit(1);
    }
}
