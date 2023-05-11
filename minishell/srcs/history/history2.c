/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:11:20 by filipa            #+#    #+#             */
/*   Updated: 2023/05/11 12:21:13 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	configurar_termcap(t_minishell_state *data)
{
	data->term_control->keystart = tgetstr("ks", 0);
	data->term_control->clear_line = tgetstr("dl", 0);
	data->term_control->up_key = tgetstr("ku", 0);
	data->term_control->down_key = tgetstr("kd", 0);
	data->term_control->cariage_return = tgetstr("cr", 0);
	data->term_control->keyend = tgetstr("ke", 0);
	if (!data->term_control->keystart
		|| !data->term_control->clear_line
		|| !data->term_control->up_key
		|| !data->term_control->down_key
		|| !data->term_control->cariage_return
		|| !data->term_control->keyend)
		free_data(data, EXIT_FAILURE);
}

int	set_history_mode(t_minishell_state *data)
{
	char	*terminalType;
	int		i;

	if (isatty(STDIN_FILENO))
	{
		terminalType = getenv("TERM");//variavel de ambiente que contem o tipo de terminal
		if (!terminalType)
		{
			write(STDOUT_FILENO, "TERM configuration not set, please set the TERM variable and try again.\n", 56);
			free_data(data, EXIT_FAILURE);
		}
		i = tgetent(0, terminalType);//atribui a estrutura termcap a terminalType, bolleana
		data->term_control = ft_calloc(1, sizeof(t_terminal_control));
		if (i != 1 || !data->term_control)
			free_data(data, EXIT_FAILURE);
		ft_bzero(&data->modified, sizeof(struct termios));
		tcgetattr(0, &data->origin);
		tcgetattr(0, &data->modified);//copia para poder ser modificada sem alterar a original
		data->modified.c_iflag &= ~(IGNBRK | BRKINT | ICRNL
				| INLCR | PARMRK | INPCK | ISTRIP | IXON);
		data->modified.c_lflag &= ~(ICANON | ECHO);
		configurar_termcap(data);
	}
	return (1);
}
/*
IGNBRK: Ignora a quebra de linha.
BRKINT: Converte uma interrupção de linha em uma interrupção de fim de arquivo.
ICRNL: Converte uma quebra de linha em um retorno de carro.
INLCR: Converte um retorno de carro em uma quebra de linha.
PARMRK: Adiciona bytes de marcação a cada caractere com erro de paridade.
INPCK: Habilita verificação de paridade.
ISTRIP: Limpa o 8º bit de cada caractere de entrada.
IXON: Desabilita o controle de fluxo de saída.
Ao utilizar o operador de bits "e" (&) com o operador "não" (~), os bits 
especificados nessas opções são desabilitados, o que significa que o programa não 
processará essas opções de entrada.

O modo canônico é um modo de operação no qual a entrada de caracteres é armazenada
em um buffer até que uma nova linha seja digitada. O modo não canônico não 
armazena a entrada de caracteres e retorna cada caractere assim que ele é digitado 
pelo usuário.
*/