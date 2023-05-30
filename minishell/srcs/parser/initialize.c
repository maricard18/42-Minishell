#include "minishell.h"

// initialize shell
void	initialize_shell(char *str)
{
    lexer(str);
	tokeniser(g_minishell.input);
	//lexer_test();
    if (validate_syntax(g_minishell.token))
		return ;
    //printf("       ["G"SYNTAX OK"RT"]\n");
    parse_commands(0, 1, g_minishell.token);
    //parser_test();
	execution();
    add_history(str);
}
