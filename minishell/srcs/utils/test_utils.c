/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:14:42 by maricard          #+#    #+#             */
/*   Updated: 2023/06/06 14:34:36 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_type(int type)
{
	if (type == 0)
		return ("PIPE");
	else if (type == 1)
		return ("OR");
	else if (type == 2)
		return ("AND");
	else if (type == 3)
		return ("GREATER");
	else if (type == 4)
		return ("SMALLER");
	else if (type == 5)
		return ("APPEND");
	else if (type == 6)
		return ("HERE_DOC");
	else if (type == 7)
		return ("OPEN_PAR");
	else if (type == 8)
		return ("CLOSE_PAR");
	else if (type == 9)
		return ("STR");
	else
		return ("ERROR");
}
