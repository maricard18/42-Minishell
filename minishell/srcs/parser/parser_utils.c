#include "minishell.h"

int count_and_or_tokens(t_token *command_token_list)//count the number of AND and OR
{
	int i;
	t_token	*current_token;

	i = 0;
	current_token = command_token_list;
	while (current_token)
	{
		if (current_token->type == AND
			|| current_token->type == OR)
			i++;
		else if (current_token->type == OPEN_PAR)
			skip_to_matching_parenthesis(&current_token);
		current_token = current_token->next;
	}
	return (i);//return the number of AND and OR
}

t_parsed *allocate_and_init_command(int in_file, int out_file)
{
	t_parsed	*command;

	command = (t_parsed *)malloc(sizeof(t_parsed));
	command->exec = 0;
	command->in_file = in_file;
	command->out_file = out_file;
	command->cmd = ft_calloc(2, sizeof(char));
	command->prev = NULL;
	command->next = NULL;
	command->file = NULL;
	command->args = ft_calloc(2, sizeof(char *));
	command->paranthesis = NULL;
	return (command);
}

void add_command_to_list(t_parsed *current_command, t_parsed **command_list)
{
	int i;

	i = 0;
	while (command_list[i])	
		i++;	
	command_list[i] = current_command;
	command_list[i + 1] = NULL;
}

//testar com funcao mario
// void handle_paranthesis(t_token **tokens_list, t_parsed **command)
// {
// 	int i;
//     t_token *command_inside_paranthesis;

// 	i = 1;
//     command_inside_paranthesis = (t_token *)ft_calloc(1, sizeof(t_token));
// 	(*command)->paranthesis = command_inside_paranthesis;
// 	(*tokens_list) = (*tokens_list)->next;
// 	while (*tokens_list && i != 0)
// 	{
// 		if ((*tokens_list)->next->type == OPEN_PAR)
// 			i++;
// 		else if ((*tokens_list)->next->type == CLOSE_PAR)
// 			i--;
// 		adiciona_token_a_lista((*tokens_list)->value, (*command)->paranthesis, (*tokens_list)->type, 2);
// 		(*tokens_list) = (*tokens_list)->next;
// 	}
// 	(*tokens_list) = (*tokens_list)->next;
// }

void skip_to_matching_parenthesis(t_token **command_token_list)
{
	int i;

	i = 0;
	while ((*command_token_list))
	{
		if ((*command_token_list)->type == OPEN_PAR)//if the token is open parenthesis
			i++;
		else if ((*command_token_list)->type == CLOSE_PAR)//if the token is close parenthesis
			i--;
		if (!i)//if i is 0, break
			break;
		(*command_token_list) = (*command_token_list)->next;//move to next token
	}
	// verificar se a funcao sintax já faz esta verificação, se nao lidar com o erro
}
