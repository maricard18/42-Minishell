/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:09:49 by maricard          #+#    #+#             */
/*   Updated: 2023/06/07 10:57:01 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_redirection_syntax(t_token *my_tokens)
{
	t_token	*tmp_tokens;

	tmp_tokens = my_tokens;
	while (tmp_tokens)
	{
		if (tmp_tokens->type == SMALLER || tmp_tokens->type == GREATER ||
			tmp_tokens->type == HERE_DOC || tmp_tokens->type == APPEND)
		{
			if (!tmp_tokens->next || tmp_tokens->next->type != STRING)
				return (handle_error(SYNTAX_ERROR,
						"Missing filename after redirection"));
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
				return (handle_error(SYNTAX_ERROR, tmp_tokens->value));
			else if (!tmp_tokens->next)
				return (handle_error(SYNTAX_ERROR,
						"Incomplete command after operator"));
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
		if (tmp_tokens->type != STRING && tmp_tokens->type != GREATER &&
			tmp_tokens->type != APPEND && tmp_tokens->type != SMALLER &&
			tmp_tokens->type != HERE_DOC && tmp_tokens->type != PIPE)
			return (handle_error(SYNTAX_ERROR, "Unrecognized token"));
		tmp_tokens = tmp_tokens->next;
	}
	return (0);
}

int	validate_syntax(t_token *my_tokens)
{
	int	error;
	int	syntax_error;

	error = 0;
	syntax_error = 0;
	error = validate_allowed_tokens(my_tokens);
	if (error != 0)
	{
		syntax_error = 1;
		handle_error(SYNTAX_ERROR, "Syntax error");
	}
	error = validate_redirection_syntax(my_tokens);
	if (error != 0)
	{
		syntax_error = 1;
		handle_error(SYNTAX_ERROR, "Syntax error");
	}
	error = validate_pipe_syntax(my_tokens);
	if (error != 0)
	{
		syntax_error = 1;
		handle_error(SYNTAX_ERROR, "Syntax error");
	}
	if (syntax_error)
		return (-1); // Retorna um valor indicando erro de sintaxe
	return (0);
}
