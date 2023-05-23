/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:20 by maricard          #+#    #+#             */
/*   Updated: 2023/05/23 14:28:31 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    append()
{
    int file;
    int fd;
    int old_fd;
    
    old_fd = dup(STDOUT_FILENO);
    file = open(g_minishell.parsed.file.name,  O_CREAT | O_WRONLY | O_APPEND, 0777);
    if (file == -1)
    {
        perror("error opening file\n");
        exit(1);
    }
    fd = dup2(file, STDOUT_FILENO);
    if (fd == -1)
    {
        perror("error on dup2()\n");
        exit(1);
    }
    close(file);
    execute_execve(g_minishell.parsed.args);
    dup2(old_fd, STDOUT_FILENO);
    close(old_fd);
    return ;
}

void    redirect_out()
{
    int file;
    int fd;
    int old_fd;

    old_fd = dup(STDIN_FILENO);
    file = open(g_minishell.parsed.file.name, O_RDONLY, 0777);
    if (file == -1)
    {
        perror("file does not exist\n");
        exit(1);
    }
    fd = dup2(file, STDIN_FILENO);
    if (fd == -1)
    {
        perror("error on dup2()\n");
        exit(1);
    }
    close(file);
    execute_execve(g_minishell.parsed.args);
    dup2(old_fd, STDIN_FILENO);
    close(old_fd);
    return ;
}

void    redirect_in()
{
    int file;
    int fd;
    int old_fd;
    
    old_fd = dup(STDOUT_FILENO);
    file = open(g_minishell.parsed.file.name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (file == -1)
    {
        perror("error opening file\n");
        exit(1);
    }
    fd = dup2(file, STDOUT_FILENO);
    if (fd == -1)
    {
        perror("error on dup2()\n");
        exit(1);
    }
    close(file);
    execute_execve(g_minishell.parsed.args); 
    dup2(old_fd, STDOUT_FILENO);
    close(old_fd);
    return ;
}
