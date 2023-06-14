/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:09:49 by maricard          #+#    #+#             */
/*   Updated: 2023/06/14 16:01:18 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_redirection_syntax(t_token *my_tokens)
{
	t_token	*tmp_tokens;

	tmp_tokens = my_tokens;
	while (tmp_tokens)
	{
		if (tmp_tokens->type == SMALLER || tmp_tokens->type == GREATER
			|| tmp_tokens->type == HERE_DOC || tmp_tokens->type == APPEND)
		{
			if (!tmp_tokens->next || tmp_tokens->next->type != STRING)
				return (1);
		}
		tmp_tokens = tmp_tokens->next;
	}
	return (0);
}

int	validate_pipe_syntax(t_token *my_tokens)
{
	t_token	*tmp_tokens;

	tmp_tokens = my_tokens;
	while (tmp_tokens)
	{
		if (tmp_tokens->type == PIPE)
		{
			if (!tmp_tokens->prev || tmp_tokens->prev->type == PIPE)
				return (1);
			else if (!tmp_tokens->next)
				return (1);
		}
		tmp_tokens = tmp_tokens->next;
	}
	return (0);
}

int	validate_allowed_tokens(t_token *my_tokens)
{
	t_token	*tmp_tokens;

	tmp_tokens = my_tokens;
	while (tmp_tokens)
	{
		if (tmp_tokens->type != STRING && tmp_tokens->type != GREATER
			&& tmp_tokens->type != APPEND && tmp_tokens->type != SMALLER
			&& tmp_tokens->type != HERE_DOC && tmp_tokens->type != PIPE)
			return (1);
		tmp_tokens = tmp_tokens->next;
	}
	return (0);
}

int	validate_syntax(t_token *my_tokens)
{
	if (validate_allowed_tokens(my_tokens) == 1)
	{
		print_error(NULL, "minishell: syntax error\n", 2);
		return (1);
	}
	if (validate_redirection_syntax(my_tokens) == 1)
	{
		print_error(NULL, "minishell: syntax error\n", 2);
		return (1);
	}
	if (validate_pipe_syntax(my_tokens) == 1)
	{
		print_error(NULL, \
					"minishell: syntax error\n", 2);
		return (1);
	}
	return (0);
}
