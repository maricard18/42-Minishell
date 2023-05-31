#include "minishell.h"

extern t_minishell_state	g_minishell;

// handle double quotes
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

// handle single quotes
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
			printf("[env variables]\n");
			i++;
			// handle_env_variables(input, &i);
		}
		else
		{
			write(1, &input[i], 1);
			i++;
		}
	}
}

// check if -n option is present
int	check_n_option(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '-')
	{
		i++;
		while (input[i] == 'n')
			i++;
	}
	if (input[i] == '\0')
		return (1);
	return (0);
}

// echo handler
void	echo_command(char **input)
{
	int	i;
	int flag;

	i = 1;
	flag = check_n_option(input[1]);
	if (flag == 1)
		i++;
	while (input[i])
	{
		put_char(input[i]);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
}
