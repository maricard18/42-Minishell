/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:20 by maricard          #+#    #+#             */
/*   Updated: 2023/05/18 16:47:41 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_files()
{
    int file;
    int dup;
    int id;
    
    id = fork();
    if (id == 0)
    {
        file = open("file", O_CREAT | O_WRONLY, 0777);
        if (file == -1)
        {
            perror("error opening file\n");
            exit(1);
        }
        dup = dup2(file, STDOUT_FILENO);
        if (dup == -1)
        {
            perror("error on dip2()\n");
            exit(1);
        }
        close(file);
    }
    else
    {
        wait(NULL);
        execute_execve(g_minishell.parser.args);   
    }
    return ;
}
