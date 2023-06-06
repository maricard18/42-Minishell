#include "minishell.h"

// initialize shell
void	initialize_shell(char *str)
{
	lexer(str);
	if (check_unfinished_quotes(g_minishell.input) == 1)
		return ;
	search_env_vars(g_minishell.input);
	tokeniser(g_minishell.input);
	lexer_test();
	if (validate_syntax(g_minishell.token))
		return ;
	printf("       [" G "SYNTAX OK" RT "]\n");
	parse_commands(0, 1, g_minishell.token);
	parser_test();
	execution();
	add_history(str);
}
