#include "minishell.h"

// pwd handler
void	pwd_command(void)
{
	char	*current_dir;

	current_dir = getcwd(0, 0);//obtem o diretório atual
	if (!current_dir)
		perror("Error while getting the current directory.");
	else
		printf("%s\n", current_dir);//imprime o diretório atual
	free(current_dir);//liberta a memória alocada para a string current_dir
}