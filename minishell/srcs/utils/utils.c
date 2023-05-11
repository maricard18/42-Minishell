/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipa <filipa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:42:53 by filipa            #+#    #+#             */
/*   Updated: 2023/05/11 18:57:02 by filipa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *var_name)//obtem o valor da variável de ambiente
{
	int		i;
	int		j;
	char	*env_str;

	i = -1;
	j = 0;
	env_str = ft_strjoin(var_name, "=");//cria uma string com o nome da variável de ambiente e o caracter '='
	while (g_minishell.ev[++i])
	{
		if (!ft_strncmp(g_minishell.ev[i], env_str, ft_strlen(env_str)))//se encontrar a variável de ambiente
		{
			while (g_minishell.ev[i][j] != '=')//avança até ao caracter '='
				j++;
			return (ft_strdup(&g_minishell.ev[i][j + 1]));//retorna o valor da variável de ambiente
		}
	}
	return (ft_calloc(sizeof(char *), 1));//se não encontrar a variável de ambiente retorna uma string vazia
}

void	update_path_directories(void)//atualiza os diretórios de busca de executáveis no shell
{
	char	*path;

	if (g_minishell.paths)//se já existir um diretório de busca de executáveis
		free_array(g_minishell.paths);//liberta a memória alocada para o array de diretórios
	path = get_env("PATH");//obtem o valor da variável de ambiente PATH
	if (!(*path))//se não existir um valor para a variável de ambiente PATH
		g_minishell.paths = 0;//o campo paths da estrutura g_minishell é definido como NULL
	else
		g_minishell.paths = ft_split(path, ':');//Divide a variável de ambiente PATH em strings separadas por ':', cada uma representando um caminho de diretório onde os executáveis podem ser encontrados. Estes são armazenados no campo paths da estrutura g_minishell
	free(path);
}

int	number_args_env_Var(void)//conta o número de variáveis de ambiente
{
	int	i;

	i = -1;
	while (g_minishell.ev[++i])
		;
	return (i);
}

void	free_array(char **arr)//liberta a memória alocada para um array de strings
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	is_whitespace(char c)//verifica se o caracter é um espaço ou um tab
{
	return (c == ' ' || c == '\t');
}
