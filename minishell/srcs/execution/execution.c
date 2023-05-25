/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:51:08 by maricard          #+#    #+#             */
/*   Updated: 2023/05/16 20:33:02 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state g_minishell;

// execute the input given
void    testing()
{
	execute_execve(g_minishell.parsed->args);
	execute_builtin_command(g_minishell.parsed->args);
    redirect_in();
	redirect_out();
	append();
	here_doc(g_minishell.parsed->args[0]);
	pipe_handle();
}

// execute the input given
void    execution()
{
    int pipe_fd[2];
    int i;
    t_parsed *temp;

    temp = g_minishell.parsed;
    i = 0;
    if (g_minishell.commands > 1)
        pipe(pipe_fd);
    while (temp)
    {
        // if (i != 1 && i % 2 != 0) // only open pipe in third iteration
        //     pipe(pipe_fd);
        if (temp->file != NULL)
            testing();
            // execute redirections and change file descriptors
        else
        {
            if (get_builtin_type(temp->args[0]) != 0)
                execute_builtin_command(temp->args);
            else
                execute_execve(temp->args);
        }
    }
}
