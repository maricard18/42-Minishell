/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:39:14 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 14:39:17 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell_state	g_minishell;

// error handler
int	handle_error(int error_code, char *custom_message)
{
	errno = error_code;
	if (errno == FILE_NOT_FOUND)
		printf("%s: No such file or directory\n", custom_message);
	else if (errno == SYNTAX_ERROR)
		printf("Syntax error near unexpected token '%s'\n", custom_message);
	else if (errno == CMD_NOT_FOUND)
		printf("Command not found: %s\n", custom_message);
	else if (errno == PERM_DENIED)
		printf("Permission denied: %s\n", custom_message);
	else if (errno == SYSTEM_ERR)
		printf("Internal code error\n");
	else if (errno == MEMORY_ERR)
		printf("Memory allocation failed\n");
	else if (errno == DUP_ERR)
		printf("Could not duplicate file descriptor\n");
	else if (errno == FORK_ERR)
		printf("Could not create fork\n");
	else if (errno == PIPE_ERR)
		printf("Could not create pipe\n");
	return (errno);
}
