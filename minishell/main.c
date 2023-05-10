#include "minishell.h"

t_minishell_state g_minishell;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*str;

	minishell_init(&g_minishell, envp);
	signal_handling();
	while (1)
	{
		signal_handling();
		str = readline(PROMPT);
		if (!str)
			break ;
		lexer(str, &g_minishell.token);
		lexer_test(&g_minishell.token);
//		clean_all(&g_minishell->token);
	}
}
