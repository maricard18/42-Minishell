#include "minishell.h"

/*void	initialize_shell(char *str)
{
    t_token *test;
    t_parsed **parsed_commands;

	test = identificar_agrupar_tokens(str);
	if (validate_syntax(test))//de estiver tudo bem segue se nao retorna
		return ;
    parsed_commands = parse_commands(0, 1, test);
    //Funçao redirecionamentos, processos filhos e a ordem de execução dos comandos com base nos operadores lógicos
	//Nessas funcoes tb sera necessario tratar da expansao das variaveis de ambiente.
}*/


int validate_syntax(t_token *my_tokens) 
{
    t_token *tmp_tokens = my_tokens;
    int paranthesis_count = 0;

    while (tmp_tokens) 
    {
        if (tmp_tokens->type == TOKEN_PIPE
            || tmp_tokens->type == TOKEN_AND
            || tmp_tokens->type == TOKEN_OR
            || tmp_tokens->type == TOKEN_CLOSE_PAR) 
        {
            if (!tmp_tokens->prev
                || tmp_tokens->prev->type == TOKEN_OPEN_PAR
                || tmp_tokens->prev->type == TOKEN_PIPE
                || tmp_tokens->prev->type == TOKEN_AND
                || tmp_tokens->prev->type == TOKEN_OR) 
            {
                return (handle_error(SYNTAX_ERROR, tmp_tokens->value));
            }
            else if (tmp_tokens->type != TOKEN_CLOSE_PAR && !tmp_tokens->next)
                return (handle_error(SYNTAX_ERROR, "Incomplete command after operator"));
        }
        if (tmp_tokens->type == TOKEN_SMALLER
            || tmp_tokens->type == TOKEN_GREATER
            || tmp_tokens->type == TOKEN_HERE_DOC
            || tmp_tokens->type == TOKEN_APPEND) 
        {
            if (!tmp_tokens->next)
                return (handle_error(SYNTAX_ERROR, "Unexpected newline after redirection symbol"));
            else if (tmp_tokens->next->type != TOKEN_STR)
                return (handle_error(SYNTAX_ERROR, tmp_tokens->next->value));
        }
        else if (tmp_tokens->type == TOKEN_OPEN_PAR)
        {
            if (tmp_tokens->prev && tmp_tokens->prev->type == TOKEN_STR)
                return (handle_error(SYNTAX_ERROR, tmp_tokens->value));
            paranthesis_count++;
        }
        else if (tmp_tokens->type == TOKEN_CLOSE_PAR) {
            if (tmp_tokens->next && tmp_tokens->next->type == TOKEN_STR) {
                return (handle_error(SYNTAX_ERROR, tmp_tokens->next->value));
            }
            paranthesis_count--;
        }
        if (!tmp_tokens->next && paranthesis_count > 0)
            return (handle_error(SYNTAX_ERROR, "Unclosed parenthesis"));
        tmp_tokens = tmp_tokens->next;
    }

    return (0);
}