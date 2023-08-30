/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:35:35 by maricard          #+#    #+#             */
/*   Updated: 2023/06/15 12:44:15 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// old pwd
void	get_current_cwd(void)
{
	g_minishell.old_pwd = getcwd(NULL, 0);
}

// update pwd
void	update_pwd(void)
{
	char	*pwd;
	char	*temp;
	int		i;

	pwd = getcwd(NULL, 0);
	if (is_include("PWD=") != -1)
	{
		i = is_include("PWD=");
		free(g_minishell.ev[i]);
		temp = ft_strjoin2("PWD=", pwd);
		g_minishell.ev[i] = ft_strdup(temp);
		free(temp);
	}
	if (is_include("OLDPWD=") != -1)
	{
		i = is_include("OLDPWD=");
		free(g_minishell.ev[i]);
		temp = ft_strjoin2("OLDPWD=", g_minishell.old_pwd);
		g_minishell.ev[i] = ft_strdup(temp);
		free(temp);
	}
	free(g_minishell.old_pwd);
	free(pwd);
}

// go to home
void	go_to_home(void)
{
	char	*temp;

	temp = get_env("HOME");
	get_current_cwd();
	if (chdir(temp) == 0)
		g_minishell.exit_status = 0;
	else
		print_error(NULL, "error: Home directory not found.\n", 1);
	free(temp);
	update_pwd();
}

// cd handler
void	cd_command(char **input)
{
	if (input[1])
	{
		get_current_cwd();
		if (input[2])
		{
			print_error(NULL, "error: too many arguments.\n", 1);
			return ;
		}
		else if (chdir(input[1]))
		{
			print_error(NULL, "error: failed to change directory.\n", 1);
			return ;
		}
		g_minishell.exit_status = 0;
		update_pwd();
	}
	else
	{
		go_to_home();
	}
}
