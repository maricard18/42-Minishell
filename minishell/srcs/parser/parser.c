/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:05:17 by maricard          #+#    #+#             */
/*   Updated: 2023/06/27 19:57:22 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// create a list with n str out dups
void	create_out_dup_list(void)
{
	t_fd		*fd;
	t_parsed	**temp;
	t_file		*file;
	int			i;

	i = -1;
	fd = (t_fd *)malloc(sizeof(t_fd));
	g_minishell.fd = fd;
	temp = g_minishell.parsed;
	while (temp[++i])
	{
		file = temp[i]->file;
		while (file)
		{
			fd->out = dup(STDOUT_FILENO);
			fd->in = dup(STDIN_FILENO);
			if (file->next || temp[i + 1])
				fd->next = (t_fd *)malloc(sizeof(t_fd));
			else
				fd->next = NULL;
			fd = fd->next;
			file = file->next;
		}
	}
}

// handle redirections
void	process_redirection(t_token **token, t_parsed **current)
{
	t_file	*file;
	t_file	*tmp_list;

	tmp_list = (*current)->file;
	file = (t_file *)malloc(sizeof(t_file));
	file->next = NULL;
	file->type = (*token)->type;
	(*token) = (*token)->next;
	file->name = ft_strdup((*token)->value);
	if (!tmp_list)
		(*current)->file = file;
	else
	{
		while (tmp_list->next)
			tmp_list = tmp_list->next;
		tmp_list->next = file;
	}
	(*token) = (*token)->next;
}

// create new command in case of pipe
t_parsed	*create_next_command(t_token **token_list, t_parsed **old_command)
{
	t_parsed	*new_cmd;

	new_cmd = init_command((*old_command)->in_file, (*old_command)->out_file);
	(*old_command)->next = new_cmd;
	new_cmd->prev = (*old_command);
	(*token_list) = (*token_list)->next;
	return (new_cmd);
}

// add command to list if it is type string
void	add_argument(t_token **token, t_parsed **current)
{
	int		i;
	char	**new_arguments;

	i = 0;
	if (!((*current)->cmd))
	{
		(*current)->cmd = ft_calloc(ft_strlen((*token)->value) + 2, \
							sizeof(char));
		ft_strcpy((*current)->cmd, (*token)->value);
	}
	while ((*current)->args[i])
		i++;
	new_arguments = ft_calloc((i + 2), sizeof(char *));
	new_arguments[i + 1] = NULL;
	new_arguments[i] = ft_strdup((*token)->value);
	while (i--)
		new_arguments[i] = ft_strdup((*current)->args[i]);
	free_array((*current)->args);
	(*current)->args = new_arguments;
	(*token) = (*token)->next;
}

// create command list
void	parse_commands(int in_file, int out_file, t_token *token)
{
	t_parsed	**list;
	t_parsed	*current;

	list = ft_calloc(token_counter(g_minishell.input) + 1, sizeof(t_parsed *));
	while (token)
	{
		current = init_command(in_file, out_file);
		add_cmd_to_list(current, list);
		while (token)
		{
			if (token->type >= 1 && token->type <= 4 && token->next)
				process_redirection(&token, &current);
			else if (token->type == STRING)
				add_argument(&token, &current);
			else if (token->type == PIPE && token->next)
			{
				current = create_next_command(&token, &current);
				add_cmd_to_list(current, list);
			}
			else
				token = token->next;
		}
	}
	g_minishell.parsed = list;
	create_out_dup_list();
}
