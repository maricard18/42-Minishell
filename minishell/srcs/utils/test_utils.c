/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:14:42 by maricard          #+#    #+#             */
/*   Updated: 2023/06/13 12:01:31 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_type(int type)
{
	if (type == 0)
		return ("PIPE");
	else if (type == 1)
		return ("GREATER");
	else if (type == 2)
		return ("SMALLER");
	else if (type == 3)
		return ("APPEND");
	else if (type == 4)
		return ("HERE_DOC");
	else if (type == 5)
		return ("STR");
	else
		return ("ERROR");
}
