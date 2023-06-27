/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:15:05 by maricard          #+#    #+#             */
/*   Updated: 2023/06/27 17:30:27 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// write to pipe inside heredoc
void	write_here_doc(int pipe_fd, char *str)
{
	write(pipe_fd, str, ft_strlen(str));
	write(pipe_fd, "\n", 1);
}

// heredoc execution process
void	exec_here_doc(char **env, int pipe_fd, t_file **file, char *str)
{
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			print_error((*file)->name, ": Delimeter Not found\n", 0);
			free(str);
			break ;
		}
		if (ft_strcmp(str, (*file)->name) == 0)
		{
			break ;
		}
		str = search_expansions(env, str);
		if ((*file)->next == NULL || (*file)->next->type != HERE_DOC)
			write_here_doc(pipe_fd, str);
		free(str);
	}
}

// parent process for heredoc
void	parent_process(int pipe[2], t_parsed *temp, t_file **file, t_fd **fd)
{
	close(pipe[1]);
	igonre_signals();
	while (waitpid(0, &g_minishell.exit_status, 0) > 0)
		continue ;
	if (WIFEXITED(g_minishell.exit_status))
		g_minishell.exit_status = WEXITSTATUS(g_minishell.exit_status);
	dup2(temp->out_file, STDOUT_FILENO);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
	*fd = (*fd)->next;
	if ((*file)->next != NULL)
	{
		*file = (*file)->next;
		return ;
	}
	else
	{
		*file = (*file)->next;
		if (temp->args[0])
			execve_or_builtin(temp->args);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
}

// heredoc handler
void	here_doc(t_parsed *temp, t_file **file, t_fd **fd)
{
	int		pipe_fd[2];
	int		pid;
	char	**env;
	char	*str;

	str = NULL;
	dup2((*fd)->out, STDOUT_FILENO);
	dup2((*fd)->in, STDIN_FILENO);
	env = g_minishell.ev;
	pipe(pipe_fd);
	signal(SIGINT, &here_doc_sigint);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		exec_here_doc(env, pipe_fd[1], file, str);
		close(pipe_fd[1]);
		exit(g_minishell.exit_status);
	}
	else
		parent_process(pipe_fd, temp, file, fd);
}
