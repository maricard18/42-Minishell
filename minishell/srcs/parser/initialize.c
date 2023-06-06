#include "minishell.h"

// initialize shell
void	initialize_shell(char *str)
{
	char **temp;

	lexer(str);
	temp = g_minishell.input;
	if (check_unfinished_quotes(temp) == 1)
		return ;
	search_env_vars(temp);
	tokeniser(temp);
	//lexer_test();
	if (validate_syntax(g_minishell.token))
		return ;
	//printf("       [" G "SYNTAX OK" RT "]\n");
	parse_commands(0, 1, g_minishell.token);
	//parser_test();
	execution();
	add_history(str);
}
