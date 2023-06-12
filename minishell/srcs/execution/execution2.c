/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:20:40 by maricard          #+#    #+#             */
/*   Updated: 2023/06/12 20:26:25 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// return the value of the mains file descriptors
void	return_fds(void)
{
	dup2(g_minishell.out, STDOUT_FILENO);
	close(g_minishell.out);
	dup2(g_minishell.in, STDIN_FILENO);
	close(g_minishell.in);
}

// function to handle env variables inside here doc
char	*search_expansions(char **env, char *str)
{
	char	*temp;
	char	*new_str;
	char	*char_str;
	int		i;

	temp = ft_calloc(1, sizeof(char));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			i++;
			temp = ft_strjoin(temp, handle_env_variables(env, str, &i)); // ! leak here ??
		}
		if (str[i] == '\0')
			break ;
		if (str[i] == '$')
			continue ;
		char_str = ft_char_string(str[i]);
		new_str = ft_strjoin(temp, char_str);
		temp = ft_strdup(new_str);
		free(new_str);
		free(char_str);
	}
	return (temp);
}

// function to open pipes
int	**open_pipes(void)
{
	int	**pipe_fd;
	int	i;
	int	a;

	i = (g_minishell.n_tokens2 - 1);
	pipe_fd = ft_calloc(i + 1, sizeof(int *));
	a = -1;
	while (++a < i)
	{
		pipe_fd[a] = malloc(sizeof(int) * 2);
		pipe(pipe_fd[a]);
	}
	return (pipe_fd);
}

// check if its a builtin command or not
void	execve_or_builtin(char **args)
{
	int	 pid;
	int	 status;

	signal(SIGINT, sigint_handler);
	status = get_builtin_type(args[0]);
	if (g_minishell.n_tokens2 > 0 && status != 0)
	{
		execute_builtin_command(args);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (status != 0)
		{
			execute_builtin_command(args);
			exit(g_minishell.exit_status);
		}
		else
			execute_execve(args);
	}
	return ;
}

// handler for execution in pipes
void	execute_commands(t_parsed *temp, t_file *file, int fd)
{
	if (file == NULL)
	{
		execve_or_builtin(temp->args);
		if (g_minishell.pipe_flag == 0 && temp->next == NULL)
			return_fds();
		return ;
	}
	while (file != NULL)
	{
		if (file->type == GREATER)
			redirect_in(temp, &file, fd);
		else if (file->type == SMALLER)
			redirect_out(temp, &file, fd);
		else if (file->type == APPEND)
			append(temp, &file, fd);
		else if (file->type == HERE_DOC)
			here_doc(temp, &file, fd);
		file = file->next;
		if (file == NULL && temp->next == NULL)
			return_fds();
	}
}
