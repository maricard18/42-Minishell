/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintestfi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipa <filipa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:00:53 by filipa            #+#    #+#             */
/*   Updated: 2023/05/20 13:03:55 by filipa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_minishell_state g_minishell;


//testar parser
void print_parsed_commands(t_parsed **command_list)
{
    int i = 0;
    while (command_list[i] != NULL)
    {
        printf("Command %d:\n", i + 1);
        printf("Exec: %d\n", command_list[i]->exec);
        printf("In file: %d\n", command_list[i]->in_file);
        printf("Out file: %d\n", command_list[i]->out_file);
        printf("Cmd: %s\n", command_list[i]->cmd);

        printf("Arguments:\n");
        int j = 0;
        char **arguments = command_list[i]->arguments;
        while (arguments[j] != NULL)
        {
            printf("%s\n", arguments[j]);
            j++;
        }

        printf("Paranthesis:\n");
        t_token *paranthesis = command_list[i]->paranthesis;
        if (paranthesis != NULL)
        {
            printf("Type: %d\n", paranthesis->type);
            printf("Value: %s\n", paranthesis->value);
        }
        
        printf("Parantheses And Or:\n");
        t_parsed **parantheses_and_or = command_list[i]->parantheses_and_or;
        if (parantheses_and_or != NULL)
        {
            int k = 0;
            while (parantheses_and_or[k] != NULL)
            {
                printf("Command %d:\n", k + 1);
                printf("Exec: %d\n", parantheses_and_or[k]->exec);
                printf("In file: %d\n", parantheses_and_or[k]->in_file);
                printf("Out file: %d\n", parantheses_and_or[k]->out_file);
                printf("Cmd: %s\n", parantheses_and_or[k]->cmd);
                printf("--------------------\n");
                k++;
            }
        }

        printf("File List:\n");
        t_file *file_list = command_list[i]->file_list;
        while (file_list != NULL)
        {
            printf("Type: %d\n", file_list->type);
            printf("Filename: %s\n", file_list->file_name);
            file_list = file_list->next;
        }

        printf("--------------------\n");
        i++;
    }
}

int main() {
    // Criação dos tokens de teste
    t_token *token1 = malloc(sizeof(t_token));
    token1->type = TOKEN_STR;
    token1->value = "ls";
    token1->prev = NULL;
    token1->next = NULL;

    t_token *token2 = malloc(sizeof(t_token));
    token2->type = TOKEN_PIPE;
    token2->value = "|";
    token2->prev = token1;
    token2->next = NULL;

    t_token *token3 = malloc(sizeof(t_token));
    token3->type = TOKEN_STR;
    token3->value = "grep";
    token3->prev = token2;
    token3->next = NULL;

    t_token *token4 = malloc(sizeof(t_token));
    token4->type = TOKEN_STR;
    token4->value = "-v";
    token4->prev = token3;
    token4->next = NULL;

    t_token *token5 = malloc(sizeof(t_token));
    token5->type = TOKEN_STR;
    token5->value = "file.txt";
    token5->prev = token4;
        token5->next = NULL;

    t_token *token6 = malloc(sizeof(t_token));
    token6->type = TOKEN_AND;
    token6->value = "&&";
    token6->prev = token5;
    token6->next = NULL;

    token1->next = token2;
    token2->next = token3;
    token3->next = token4;
    token4->next = token5;
    token5->next = token6;
    token6->next = NULL;

    // Chamar a função validate_syntax com os tokens de teste
    int result = validate_syntax(token1);

    if (result == 0) 
    {
        printf("Syntax is valid\n");
    }

    return 0;
}




/*int main() {

t_token* token_sequence = (t_token*)malloc(sizeof(t_token) * 15);

token_sequence[0].type = TOKEN_GREATER;
token_sequence[0].value = "lol";
token_sequence[0].prev = NULL;
token_sequence[0].next = &token_sequence[1];

token_sequence[1].type = TOKEN_STR;
token_sequence[1].value = "echo";
token_sequence[1].prev = &token_sequence[0];
token_sequence[1].next = &token_sequence[2];

token_sequence[2].type = TOKEN_GREATER;
token_sequence[2].value = "test";
token_sequence[2].prev = &token_sequence[1];
token_sequence[2].next = &token_sequence[3];

token_sequence[3].type = TOKEN_GREATER;
token_sequence[3].value = "lol";
token_sequence[3].prev = &token_sequence[2];
token_sequence[3].next = &token_sequence[4];

token_sequence[4].type = TOKEN_GREATER;
token_sequence[4].value = "test";
token_sequence[4].prev = &token_sequence[3];
token_sequence[4].next = &token_sequence[5];

token_sequence[5].type = TOKEN_APPEND;
token_sequence[5].value = "lol";
token_sequence[5].prev = &token_sequence[4];
token_sequence[5].next = &token_sequence[6];

token_sequence[6].type = TOKEN_GREATER;
token_sequence[6].value = "test";
token_sequence[6].prev = &token_sequence[5];
token_sequence[6].next = &token_sequence[7];

token_sequence[7].type = TOKEN_STR;
token_sequence[7].value = "mdr";
token_sequence[7].prev = &token_sequence[6];
token_sequence[7].next = &token_sequence[8];

token_sequence[8].type = TOKEN_GREATER;
token_sequence[8].value = "lol";
token_sequence[8].prev = &token_sequence[7];
token_sequence[8].next = &token_sequence[9];

token_sequence[9].type = TOKEN_STR;
token_sequence[9].value = "test";
token_sequence[9].prev = &token_sequence[8];
token_sequence[9].next = &token_sequence[10];

token_sequence[10].type = TOKEN_GREATER;
token_sequence[10].value = "lol";
token_sequence[10].prev = &token_sequence[9];
token_sequence[10].next = &token_sequence[11];

token_sequence[11].type = TOKEN_STR;
token_sequence[11].value = "test";
token_sequence[11].prev = &token_sequence[10];
token_sequence[11].next = &token_sequence[12];

token_sequence[12].type = TOKEN_APPEND;
token_sequence[12].value = "lol";
token_sequence[12].prev = &token_sequence[11];
token_sequence[12].next = &token_sequence[13];

token_sequence[13].type = TOKEN_STR;
token_sequence[13].value = "mdr";
token_sequence[13].prev = &token_sequence[12];
token_sequence[13].next = &token_sequence[14];

token_sequence[14].type = TOKEN_STR;
token_sequence[14].value = NULL;
token_sequence[14].prev = &token_sequence[13];
token_sequence[14].next = NULL;
    // Chamada da função parse_commands
    t_parsed **command_list = parse_commands(0, 1, token_sequence);

	  // Imprimir a estrutura resultante
    print_parsed_commands(command_list);
    
    // Liberar memória alocada
    free(token_sequence);
    
    return 0;
    
}
*/

/*
int main()
{
    // Exemplo de tokens
    t_token *token_sequence = (t_token *)malloc(sizeof(t_token) * 10);
    token_sequence[0].type = TOKEN_STR;
    token_sequence[0].value = "echo";
    token_sequence[0].prev = NULL;
    token_sequence[0].next = &token_sequence[1];
    
    token_sequence[1].type = TOKEN_STR;
    token_sequence[1].value = "Hello";
    token_sequence[1].prev = &token_sequence[0];
    token_sequence[1].next = &token_sequence[2];
    
    token_sequence[2].type = TOKEN_STR;
    token_sequence[2].value = "World";
    token_sequence[2].prev = &token_sequence[1];
    token_sequence[2].next = NULL;
    
    // Chamar a função parse_commands
    t_parsed **command_list = parse_commands(0, 1, token_sequence);
    
    // Imprimir a estrutura resultante
    print_parsed_commands(command_list);
    
    // Liberar memória alocada
    free(token_sequence);
    
    return 0;
}*/