#include "minishell.h"

void	env_command(void)
{
	char	**env;

	env = g_minishell.ev;//array de variáveis de ambiente armazenado em g_minishell.ev
	while (*env)
	{
		printf("%s\n", *env);//imprime cada variável de ambiente
		env++;
	}
	if (g_minishell.parent_pid != getpid())
		exit(0);
}