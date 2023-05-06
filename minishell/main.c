#include "minishell.h"

t_minishell_state g_data;

int	env_size(char **env)
{
<<<<<<< HEAD
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

=======
	char	*str;

	str = readline(PROMPT);
>>>>>>> ef150b119c54bc7542ca266bac7262852c5c3f96
	return (0);
}
