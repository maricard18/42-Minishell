#include "minishell.h"

t_minishell_state g_data;

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (++i);
}

char	**env_dup(char **env)
{
	char	**env_array;
	int		i;

	i = 0;
	env_array = malloc(sizeof(char *) * env_size(env));
	if (!env_array)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		env_array[i] = ft_strdup(env[i]);
		i++;
	}
	env_array[i] = 0;
	return (env_array);
}


void	minishell_init(t_minishell_state *shell, char **env)
{
	shell->prompt = "\x1b[32m[\x1b[33mMinishell\x1b[32m]~>\x1b[0m ";
	shell->status = 0;
	shell->status_signal = 0;
	shell->input = NULL;
	shell->environment_variables = env_dup(env);
	if (!shell->environment_variables)
		exit(EXIT_FAILURE);
	shell->pwd = getcwd(NULL, 0);
	shell->fd_in = 0;
	shell->fd_out = 1;
	shell->any_redirection = 1;
	shell->history_head = NULL;
	shell->history_index = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	prompt();
	minishell_init(&g_data, envp);

	return (0);
}

/*
Imagine that your computer is a big toy box, and each toy is a program. The toys need some 
information to work properly, like instructions on how to play with them or some special settings. 
These pieces of information are called environment variables.

When you start a program (take a toy out of the box), it gets a list of these environment variables 
so it knows how to work correctly. This list of variables is called envp. It's like a small note that 
comes with the toy, telling you how to play with it or set it up.

In your minishell program, envp is a list of these notes that you can use to make your program work 
correctly and do things like remember where other programs are or how to set up special features.
*/