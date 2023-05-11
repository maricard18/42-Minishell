#include "minishell.h"

int	number_args(char **input)//conta o numero de argumentos
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}

int	number_signal(char *arg)//verifica se o argumento é um numero com sinal
{
	while (*arg)
	{
		if ((*arg >= '0' && *arg <= '9') || *arg == '+' || *arg == '-')
			arg++;
		else
			return (0);
	}
	return (1);
}

//termina imediatamente a execução do programa e retorna o controle para o sistema operacional.
void	exit_command(char **input)//encerra o programa
{
	if (number_args(input) == 1)//se for só exit
	{
		printf("minishell: exit: no argument provided\n");
		exit(errno);
	}
	else
	{
		if (number_signal(input[1]))//
		{
			if (number_args(input) > 2)//se for exit + numero + argumento
			{
				write(2, "exit\nEXIT: too many arguments\n", 41);
				errno = 1;
				return ;
			}
			exit(ft_atoi(input[1]) % 256);//valor no intervalo de 0 a 255 para garantir a compatibilidade e consistência com outros programas e scripts
		}
		write(2, "exit\nminishell: exit: numeric argument required\n", 48);
        exit(-1);//valor no intervalo de 0 a 255 para garantir a compatibilidade e consistência com outros programas e scripts
		//exit(-1 % 256);//Ao aplicar a operação de módulo (%) por 256 ao valor -1, garante que o resultado esteja dentro do intervalo válido
	}
}
//retornar um código de saída que indica o status de encerramento do programa 