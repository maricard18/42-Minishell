#include "minishell.h"

void	remove_env_var(char *data)//remove uma variável de ambiente
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(sizeof(char *), number_args_env_var() + 1);//aloca memória para um array de strings com o número de variáveis de ambiente + 1
	while (g_minishell.ev[i])
	{
		if (ft_strncmp(g_minishell.ev[i], data, ft_strlen(data)))//se a variável de ambiente não for igual à variável a remover
		{
			new_env[j] = ft_strdup(g_minishell.ev[i]);//copia a variável de ambiente para o novo array
			j++;
		}
		i++;
	}
	new_env[j] = 0;//termina o array com NULL
	free_array(g_minishell.ev);//liberta a memória alocada para o array de variáveis de ambiente
	g_minishell.ev = new_env;//atualiza o array de variáveis de ambiente
}

void	unset_command(char **input)//emover variáveis de ambiente no shell
{
	char	*data;

	input++;//avança para o primeiro argumento
	while (*input)
	{
		data = ft_strjoin(*input, "=");//cria uma string com o argumento e o =
		remove_env_var(data);//remove a variável de ambiente
		input++;
	}
	free(data);
	update_path_directories();//atualiza os caminhos
}