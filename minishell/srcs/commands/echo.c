#include "minishell.h"

extern t_minishell_state	g_minishell;

void	handle_double_quotes(char *input, int *i)
{
	(*i)++;
	while (input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			printf("[handle env variables]");
			// handle_env_variables(input, i);
			(*i)++;
		}
		write(1, &input[*i], 1);
		(*i)++;
	}
	if (input[*i] == '"')
		(*i)++;
}

void 		handle_single_quotes(char *input, int *i)
{
	(*i)++;
	while (input[*i] != '\'')
	{
		write(1, &input[*i], 1);
		(*i)++;
	}
	if (input[*i] == '\'')
		(*i)++;
}

// write character
void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
			handle_double_quotes(input, &i);
		else if (input[i] == '\'')
			handle_single_quotes(input, &i);
		else if (input[i] == '$')
		{
			printf("[handle env variables]");
			// handle_env_variables(input, &i);
			i++;
		}
		else
		{
			write(1, &input[i], 1);
			i++;
		}
	}
}

// echo handler
void	echo_command(char **input)
{
	int	i;

	i = 1;
	while (!ft_strcmp(input[i], "-n"))
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
