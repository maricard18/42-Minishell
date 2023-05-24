#include "minishell.h"

// write character
void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		write(1, &input[i], 1);
		i++;
	}
}

// echo handler
void	echo_command(char **input)
{
	int	i;

	i = 1;
	while (!ft_strcmp(input[i], "-n"))//-n indica não imprimir uma nova linha
		i++;
	while (input[i])
	{
		put_char(input[i]);//imprime os argumentos
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);//adiciona um espaço entre os argumentos
		i++;
	}
	if (ft_strcmp(input[1], "-n"))//verifica se o primeiro argumento é -n
		write(STDOUT_FILENO, "\n", 1);//se não for, imprime uma nova linha
	if (g_minishell.parent_pid != getpid())//não for o processo pai do minishell
		exit(0);
}