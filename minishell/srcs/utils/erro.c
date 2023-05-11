#include "minishell.h"

int handle_error(int error_code, char *custom_message)// função que trata os erros.
{
    errno = error_code;// errno é uma variável global que armazena o código de erro.
    if (errno == FILE_NOT_FOUND)
        printf("%s: No such file or directory\n", custom_message);
    else if (errno == SYNTAX_ERROR)// se o erro for de sintaxe
        printf("Syntax error near unexpected token '%s'\n", custom_message);
    else if (errno == CMD_NOT_FOUND)// se o comando não for encontrado
        printf("Command not found: %s\n", custom_message);
    else if (errno == PERM_DENIED)// se o usuário não tiver permissão
        printf("Permission denied: %s\n", custom_message);
    else if (errno == SYSTEM_ERR)// se houver um erro interno
        printf("Internal code error\n");
    else if (errno == MEMORY_ERR)// se houver um erro de alocação de memória
        printf("Memory allocation failed\n");
    else if (errno == DUP_ERR)// se houver um erro de duplicação de descritor de arquivo
        printf("Could not duplicate file descriptor\n");
    else if (errno == FORK_ERR)// se houver um erro de fork
        printf("Could not create fork\n");
    else if (errno == PIPE_ERR)// se houver um erro de pipe
        printf("Could not create pipe\n");
    if (g_minishell.parent_pid != getpid())// se o pid do processo pai for diferente do pid do processo atual
        exit(errno);
    return (errno);// retorna o código de erro
}
