#include "minishell.h"

void	initialize_shell(char *str)
{
    t_token *test;
    //t_parsed **parsed_commands;

	//test = funçao_para_dividir_guardar_e_identificar_tokens
	if (validate_syntax(test))//de estiver tudo bem segue se nao retorna
		return ;
    //Funcao para a analise a lista de tokens e crie uma estrutura de dados que represente os comandos a serem executados.
    //Funçao redirecionamentos, processos filhos e a ordem de execução dos comandos com base nos operadores lógicos
	//Nessas funcoes tb sera necessario tratar da expansao das variaveis de ambiente.
}


//next_token(t_token *my_tokens)//próximo token a partir da entrada do usuário e adicioná-lo à lista de tokens
{
    t_token *tmp_tokens;
    t_token *new_tokens;
    char *user_input;

    tmp_tokens = my_tokens;
    while (tmp_tokens->next)
        tmp_tokens = tmp_tokens->next;//percorrem a lista de tokens my_tokens até chegar ao último nó
    user_input = readline("> ");//obter a entrada do usuário. O prompt "> " é exibido para pedir a entrada
    //new_tokens = funcao para extrair os tokens separa-los e guarda-los para converter a entrada do usuário em uma lista de tokens new_tokens
    new_tokens->prev = tmp_tokens;//atualizam os ponteiros prev e next para adicionar new_tokens como o próximo nó na lista de tokens
    tmp_tokens->next = new_tokens;
}

int validate_syntax(t_token *my_tokens)//comandos sejam interpretados corretamente e executados adequadamente
{
    t_token *tmp_tokens;
    int paranthesis_count;

    tmp_tokens = my_tokens;
    paranthesis_count = 0;//número de parênteses abertos e fechados
    while (tmp_tokens)//percorre a lista
    {//se o simbolo for algum dos defenidos
        if (tmp_tokens->type == TOKEN_PIPE
            || tmp_tokens->type == TOKEN_AND
            || tmp_tokens->type == TOKEN_OR
            || tmp_tokens->type == TOKEN_CLOSE_PAR)
        {// e nao houver token anterior ou o token anterior for algum dos defenidos
            if (!tmp_tokens->prev
                || tmp_tokens->prev->type == TOKEN_OPEN_PAR
                || tmp_tokens->prev->type == TOKEN_PIPE
                || tmp_tokens->prev->type == TOKEN_AND
                || tmp_tokens->prev->type == TOKEN_OR)
                return (handle_error(SYNTAX_ERROR, tmp_tokens->value));//erro de sintaxe
            else if (tmp_tokens->type != TOKEN_CLOSE_PAR
                && !tmp_tokens->next)//e não houver um próximo token, o comando não está completo
            {
                //funçao para chegar ao proximo token next_token(tmp_tokens)
                break ;
            }
        }
        if (tmp_tokens->type == TOKEN_SMALLER
            || tmp_tokens->type == TOKEN_GREATER
            || tmp_tokens->type == TOKEN_HERE_DOC
            || tmp_tokens->type == TOKEN_APPEND)
        {
            if (!tmp_tokens->next)//nao houver proximo token
                return (handle_error(SYNTAX_ERROR, "Unexpected newline after redirection symbol"));
            else if (tmp_tokens->next->type != TOKEN_STR)//token não é do tipo string
                return (handle_error(SYNTAX_ERROR, tmp_tokens->next->value));//mensagem de erro indicando um erro de sintaxe específico
        }
        else if (tmp_tokens->type == TOKEN_OPEN_PAR)// se é (
        {
            if (tmp_tokens->prev && tmp_tokens->prev->type == TOKEN_STR)//significa que existe um comando sem operador
                return (handle_error(SYNTAX_ERROR, tmp_tokens->value));
            paranthesis_count++;
        }
        else if (tmp_tokens->type == TOKEN_CLOSE_PAR)
        {
            if (tmp_tokens->next && tmp_tokens->next->type == TOKEN_STR)
                return (handle_error(SYNTAX_ERROR, tmp_tokens->next->value));
            paranthesis_count--;
        }
        if (!tmp_tokens->next && paranthesis_count > 0)// se nao houver mais tokens e ainda tiver ( por fechar paranthesis > 0
        {
            //funçao para chegar ao proximo token next_token(tmp_tokens)
            break ;
        }
        tmp_tokens = tmp_tokens->next;
    }
    return (0);// se estiver tudo ok
}