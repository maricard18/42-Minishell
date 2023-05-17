#include "minishell.h"

int	get_builtin_type(char *command)// é um dos comandos built-in conhecidos.
{
	if (!ft_strcmp(command, "cd"))// se o comando for cd
		return (CD);// retorna o valor CD
	if (!ft_strcmp(command, "env"))
		return (ENV);
	if (!ft_strcmp(command, "pwd"))
		return (PWD);
	if (!ft_strcmp(command, "echo"))
		return (ECHO_);
	if (!ft_strcmp(command, "exit"))
		return (EXIT);
	if (!ft_strcmp(command, "unset"))
		return (UNSET);
	if (!ft_strcmp(command, "export"))
		return (EXPORT);
	return (0);
}

void	execute_builtin_command(char **arguments)
{
	int	type;

	type = get_builtin_type(arguments[0]);
	if (type == CD)
		cd_command(arguments);
	if (type == ENV)
		env_command();
	if (type == PWD)
		pwd_command();
	if (type == ECHO_)
		echo_command(arguments);
	if (type == EXIT)
		exit_command(arguments);
	if (type == UNSET)
		unset_command(arguments);
	if (type == EXPORT)
		exit_command(arguments);
}