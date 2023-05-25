/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:34:12 by maricard          #+#    #+#             */
/*   Updated: 2023/05/25 18:56:17 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structs.h"
# include "functions.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

# define B "\033[1m\033[30m"
# define R "\033[1m\033[31m"
# define G "\033[1m\033[32m"
# define Y "\033[1m\033[33m"
# define BL "\033[1m\033[34m"
# define P "\033[1m\033[35m"
# define CY "\033[1m\033[36m"
# define RT "\033[0m"

// # define PROMPT "\x1b[32m[\x1b[33mMinishell\x1b[32m]~>\x1b[0m "
# define PROMPT " [mini\033[31;1mshell] \033[0m"

#endif