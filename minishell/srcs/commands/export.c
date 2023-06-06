#include "minishell.h"

int	check_env_var(char *str)//verifica se a variável de ambiente é válida
{
	char	*equal_sign_ptr;

	equal_sign_ptr = ft_strchr(str, '=');//
	if (!equal_sign_ptr || (equal_sign_ptr == str))//se nao tiver = ou se o = for o primeiro caracter
		return (0);
	while (*str)
	{
		if (is_whitespace(*str))//se for um espaço
			return (0);
		str++;
	}
	return (1);
}

void	add_env_var(char *str)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_calloc(sizeof(char *), number_args_env_var() + 2);//+ 2 para a nova variável e o NULL
	while (g_minishell.ev[++i])
		new_env[i] = ft_strdup(g_minishell.ev[i]);//copia as variáveis de ambiente para a nova variável
	new_env[i] = ft_strdup(str);//copia a nova variável
	free_array(g_minishell.ev);//liberta a memória da variável de ambiente antiga
	g_minishell.ev = new_env;//aponta a variável de ambiente para a nova variável
}

int	is_include(char *str)//verifica se a variável de ambiente já existe
{
	int		i;
	int		j;

	i = 0;
	while (g_minishell.ev[i])//percorre a variável de ambiente
	{
		j = 0;
		while (g_minishell.ev[i][j] && str[j])//percorre a variável de ambiente e a nova variável
		{
			if (str[j] == '=' && g_minishell.ev[i][j] == '=')//se encontrar o = nas duas variáveis
				return (i);//retorna a posição da variável de ambiente
			if (str[j] != g_minishell.ev[i][j])//se encontrar um caracter diferente
				break ;
			j++;
		}
		i++;
	}
	return (-1);//se não encontrar a variável de ambiente
}

void	export_command(char **input)//exporta as variáveis de ambiente
{
	int		index;

	input++;//avança para o primeiro argumento
	while (*input)
	{
		if (check_env_var(*input))//verifica se o argumento é uma variável de ambiente
		{
			index = is_include(*input);//verifica se a variável de ambiente já existe
			if (index != -1)//se existir
				g_minishell.ev[index] = ft_strdup(*input);//substitui a variável de ambiente
			else
				add_env_var(*input);//adiciona a variável de ambiente
		}
		input++;
	}
	update_path_directories();//atualiza os diretórios de busca de executáveis no shell
}
/*
Os diretórios de busca de executáveis no shell são 
os sitios onde o shell procura por programas executáveis quando
digitamos um comando. Quando digitamos um comando, o shell 
verifica esses diretórios e procura o programa correspondente 
e, se encontrado, executa-o.

variável de ambiente "PATH", que é uma variável 
especial que tem os diretórios separados por ':'
*/