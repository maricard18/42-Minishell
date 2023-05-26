#include "minishell.h"

// initialize shell
void	initialize_shell(char *str)
{
    // t_parsed **parsed_commands;

    lexer(str);
	tokeniser(g_minishell.input);
	// lexer_test();
    if (validate_syntax(g_minishell.token))
		return ;
    // printf("     ["G"SYNTAX OK"RT"]\n");
    // parsed_commands = parse_commands(0, 1, g_minishell.token);
    // parser_test();
	execution();
    // testing();
    add_history(str);
}
