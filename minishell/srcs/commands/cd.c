#include "minishell.h"

void	cd_command(char **input)
{
	if (input[1])//diretorio existe
	{
		if (chdir(input[1]))//Ela muda o diretório de trabalho atual do processo que a chama para o diretório especificado em path.
			perror("Failed to change directory");
	}
	else
		if (chdir(getenv("HOME")))
			perror("Home directory not found");
	if (g_minishell.parent_pid != getpid())//não for o processo pai do minishell
		exit(errno);//encerrado adequadamente e retorna o código erro
}