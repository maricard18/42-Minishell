/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:26:56 by maricard          #+#    #+#             */
/*   Updated: 2023/05/26 10:02:57 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_env_var(char **ev)//duplica a variavel de ambiente
{
	int		i;
	char	**env_copy;

	i = 0;
	while (ev[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i + 1));//aloca memoria para o array de variaveis de ambiente
	if (!env_copy)
		return (0);
	i = -1;
	while (ev[++i])//copia as variaveis de ambiente para o array
		env_copy[i] = ft_strdup(ev[i]);
	env_copy[i] = 0;
	return (env_copy);
}

// init minishell variables
void	minishell_init(char **ev)
{
    errno = 0;//limpa qualquer codigo de erro anterior
	g_minishell.parent_pid = getpid();//armazena ID
    g_minishell.child_pids = (int *)malloc(sizeof(int) * 100);//aloca memoria para o array de pids
    g_minishell.child_pids_count = 0;//inicializa o contador de pids filhos
    g_minishell.opening_prompt = 0;//inicia a flag de prompt, determinar se o shell está no processo de exibir um prompt.
    g_minishell.in_file = STDIN_FILENO;//inicializa o arquivo de entrada
    g_minishell.out_file = STDOUT_FILENO;//inicializa o arquivo de saida
	g_minishell.ev = dup_env_var(ev);//duplica a variavel de ambiente
	g_minishell.paths = ft_split(getenv("PATH"), ':');//Divide a variável de ambiente PATH em strings separadas por ':', cada uma representando um caminho de diretório onde os executáveis podem ser encontrados. Estes são armazenados no campo paths da estrutura g_minishell


	g_minishell.parsed = malloc(sizeof(t_parsed));
	g_minishell.parsed->args = malloc(sizeof(char *) * 2);
	g_minishell.parsed->args[0] = ft_strdup("cal");
	g_minishell.parsed->args[1] = NULL;
	
	g_minishell.parsed->next = malloc(sizeof(t_parsed));
	g_minishell.parsed->next->args = malloc(sizeof(char *) * 3);
	g_minishell.parsed->next->args[0] = ft_strdup("grep"); 
	g_minishell.parsed->next->args[1] = ft_strdup("7");
	g_minishell.parsed->next->args[2] = NULL;
	
	g_minishell.parsed->next->next = malloc(sizeof(t_parsed));
	g_minishell.parsed->next->next->args = malloc(sizeof(char *) * 3);
	g_minishell.parsed->next->next->args[0] = ft_strdup("wc"); 
	g_minishell.parsed->next->next->args[1] = ft_strdup("-w");
	g_minishell.parsed->next->next->args[2] = NULL;

	g_minishell.parsed->next->next->next = NULL;
	// g_minishell.parsed.file->type = STRING;
	// g_minishell.parsed.file->name = "1";
	// g_minishell.parsed.next = NULL;
}
