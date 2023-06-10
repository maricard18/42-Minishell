/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:34:12 by maricard          #+#    #+#             */
/*   Updated: 2023/06/10 17:43:26 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "functions.h"
# include "libft.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define B "\033[1m\033[30m"
# define R "\033[1m\033[31m"
# define G "\033[1m\033[32m"
# define Y "\033[1m\033[33m"
# define BL "\033[1m\033[34m"
# define P "\033[1m\033[35m"
# define CY "\033[1m\033[36m"
# define RT "\033[0m"
# define W "\033[1m"

# define PROMPT "\033[1m[mini\033[1m\033[31mshell]\033[0m "

#endif