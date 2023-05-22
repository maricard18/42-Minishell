/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:20 by maricard          #+#    #+#             */
/*   Updated: 2023/05/22 16:23:49 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_files()
{
    int file;
    int fd;
    int old_fd;
    
    old_fd = dup(STDOUT_FILENO);
    file = open(g_minishell.parser.file.name, O_CREAT | O_WRONLY, 0777);
    if (file == -1)
    {
        perror("error opening file\n");
        exit(1);
    }
    fd = dup2(file, STDOUT_FILENO);
    if (fd == -1)
    {
        perror("error on dip2()\n");
        exit(1);
    }
    close(file);
    execute_execve(g_minishell.parser.args); 
    dup2(old_fd, STDOUT_FILENO);
    close(old_fd);
    return ;
}
