/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:20 by maricard          #+#    #+#             */
/*   Updated: 2023/05/23 20:42:42 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pipe_handle()
{
    int pipe_fd[2];
    int pid;
    int fd_out;
    int fd_in;

    fd_out = dup(STDOUT_FILENO);
    fd_in = dup(STDIN_FILENO);
    if (pipe(pipe_fd) == -1)
    {
        printf("pipe error\n");
        exit(1);
    }
    pid = fork();
    if (pid == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        execute_execve(g_minishell.parsed.args);
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
    else
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        execute_execve(g_minishell.parsed.next->args);
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
        wait(NULL);
    }
}

void    here_doc(char *keyword)
{
    char *str;

    while (1)
    {
        str = readline("> ");
        if (!str)
        {
            printf("did not found keywork: %s\n", keyword);
            break ;
        }
        if (ft_strcmp(str, keyword) == 0)
            break ;
    }
}

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
