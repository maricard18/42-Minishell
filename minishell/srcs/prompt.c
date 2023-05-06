/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:20:42 by maricard          #+#    #+#             */
/*   Updated: 2023/04/21 20:38:15 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void yellow()
{
	printf("\033[1;33m");
}

void red()
{
	printf("\033[1;31m");
}

void white()
{
	printf("\033[1;37m");
}

void prompt()
{
	yellow();
	printf(" mini");
	red();
	printf("shell");
	white();
	printf(" | ");
}
