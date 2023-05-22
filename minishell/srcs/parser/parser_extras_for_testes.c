#include "minishell.h"

#define DOUBLE_QUOTE "\""
#define SINGLE_QUOTE "'"

//ok
int carater_especial(char c)
{
    if (ft_strchr("|&><()", c))
        return 0;
    return 1;
}

//ok
int ve_se_tem_na_string(char *string, char *chars_to_search, size_t size)//procura um conjunto de caracteres numa string
{
    int i;
    int k;

    k = -1;
    while (string[++k] && size-- > 0)
    {
        i = -1;
        while (chars_to_search[++i])
            if (chars_to_search[i] == string[k])
                return 0;//se encontrar um dos caracteres retorna 0
    }
    return -1;//se não encontrar nenhum dos caracteres retorna -1
}

//ok
int encontra_o_par(char *input, char c)//procura o par de aspas simples ou aspas duplas ou parentesis
{
    int i;
    char *tmp;

    i = 0;
    tmp = input;
    while (*(tmp + ++i))
    {
        if (*(tmp + i) == c)
            return i;
    }
    return -1;
}

//ok
int retorna_strings(char *input)//análise léxica de uma string input para identificar o token
{
    int i;

    i = 0;
    while (*(input + i) && carater_especial(*(input + i))
        && ve_se_tem_na_string((input + i), " \t\n", 1))
    {
        if (*(input + i) == *DOUBLE_QUOTE)
            i += encontra_o_par(input + i, *DOUBLE_QUOTE) + 1;
        else if (*(input + i) == *SINGLE_QUOTE)
            i += encontra_o_par(input + i, *SINGLE_QUOTE) + 1;
        else
            i++;
    }
    return i;//encontrar a posição do primeiro token na string de entrada
    //ignora carateres especiais, ignora " \t\n" e ignora aspas simples e aspas duplas
    //ou seja so retorna strings que sao comandos ou -L
}

//ok

int adiciona_token_a_lista(char *input, t_token *tokens_list, enum tokens type, int size)//adiciona um token à lista ligada
{
    t_token *token;
    t_token *tmp_table;

    if (type == TOKEN_STR)
        size = retorna_strings(input);//encontrar a posição do primeiro token na string de entrada
    token = (t_token *)malloc(sizeof(t_token));
    token->type = type;
    token->value = ft_substr(input, 0, size);
    token->next = NULL;
    token->prev = NULL;
    tmp_table = tokens_list;
    if (!(tokens_list->value))
    {
        tokens_list->value = ft_substr(input, 0, size);
        tokens_list->next = NULL;
        tokens_list->prev = NULL;
        tokens_list->type = type;
    }
    else
    {
        while (tmp_table->next)
            tmp_table = tmp_table->next;
        token->prev = tmp_table;
        tmp_table->next = token;
    }
    return (size);
}

//ok
void analisa_e_atribui_significado(char *input, t_token *tokens_list)//encontra o token e adiciona à lista ligada
{
    while (*(input))
    {
        if (*(input) == '&' && *(input + 1) == '&')
            input += adiciona_token_a_lista(input, tokens_list, TOKEN_AND, 2);
        else if (*(input) == '(')
            input += adiciona_token_a_lista(input, tokens_list, TOKEN_OPEN_PAR, 1);
        else if (*(input) == ')')
            input += adiciona_token_a_lista(input, tokens_list, TOKEN_CLOSE_PAR, 1);
        else if (*(input) == '|')
            if (*(input + 1) == '|')
                input += adiciona_token_a_lista(input, tokens_list, TOKEN_OR, 2);
            else
                input += adiciona_token_a_lista(input, tokens_list, TOKEN_PIPE, 1);
        else if (*(input) == '>')
            if (*(input + 1) == '>')
                input += adiciona_token_a_lista(input, tokens_list, TOKEN_APPEND, 2);
            else
                input += adiciona_token_a_lista(input, tokens_list, TOKEN_GREATER, 1);
        else if (*(input) == '<')
            if (*(input + 1) == '<')
                input += adiciona_token_a_lista(input, tokens_list, TOKEN_HERE_DOC, 2);
            else
                input += adiciona_token_a_lista(input, tokens_list, TOKEN_SMALLER, 1);
        else if (*(input) == ' ' || *(input) == '\t' || *(input) == '\n')
            input += 1;
        else
            input += adiciona_token_a_lista(input, tokens_list, TOKEN_STR, 0);
    }
}


//ok
t_token *identificar_agrupar_tokens(char *input)//identifica e agrupa os tokens
{
    t_token *command_table;

    command_table = (t_token *)ft_calloc(1, sizeof(t_token));
    analisa_e_atribui_significado(input, command_table);
    return (command_table);
}