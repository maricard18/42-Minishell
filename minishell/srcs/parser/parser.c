#include "minishell.h"

void process_redirection(t_token **tokens_list, t_parsed **current_command)//alocação de memoria para a strct t_file em caso de existir um redirecionamento
{
	t_file	*file;
	t_file	*tmp_list;

	tmp_list = (*current_command)->file;//tmp_list is a pointer to the file
	file = (t_file *)malloc(sizeof(t_file));//allocate memory for the file
	file->next = NULL;
	file->type = (*tokens_list)->type;//file_list->type is the type of the token
	(*tokens_list) = (*tokens_list)->next;
	file->name = (*tokens_list)->value;
	if (!tmp_list)
		(*current_command)->file = file;
	else
	{
		while (tmp_list->next)
			tmp_list = tmp_list->next;
		tmp_list->next = file;
	}
	(*tokens_list) = (*tokens_list)->next;
}

t_parsed *create_next_command(t_token **token_list, t_parsed **old_command)
{
	t_parsed *new_command;

	new_command = allocate_and_init_command((*old_command)->in_file, (*old_command)->out_file);
	(*old_command)->next = new_command;
	new_command->prev = (*old_command);
	(*token_list) = (*token_list)->next;
	return (new_command);
}

void add_argument(t_token **tokens_list, t_parsed **command)
{
	int	i;
	char **new_arguments;

	i = 0;
	if (!((*command)->cmd))
	{
		(*command)->cmd = ft_calloc(ft_strlen((*tokens_list)->value) + 2, sizeof(char));
		ft_strcpy((*command)->cmd, (*tokens_list)->value);
	}
	while ((*command)->args[i])
		i++;
	new_arguments = ft_calloc((i + 2), sizeof(char *));
	new_arguments[i + 1] = NULL;
	new_arguments[i] = ft_strdup((*tokens_list)->value);
	while (i--)
		new_arguments[i] = ft_strdup((*command)->args[i]);
	free_array((*command)->args);
	(*command)->args = new_arguments;
	(*tokens_list) = (*tokens_list)->next;
}

t_parsed	**parse_commands(int in_file, int out_file, t_token *token_sequence)
{
	t_parsed	**command_list;//array de arrays of commands caso nao tenha and e or ira ser apenas um array
	t_parsed	*current_command;//array of commands

	//command_list = ft_calloc(count_and_or_tokens(token_sequence) + 2, sizeof(t_parsed *));// + 2 for NULL
	command_list = ft_calloc(token_counter(g_minishell.input) + 1, sizeof(t_parsed *));
	while (token_sequence)
	{
		current_command = allocate_and_init_command(in_file, out_file);
		if (!token_sequence->prev)//if first command
			current_command->exec = 3;//exec is always 3 for first command
		else
			current_command->exec = token_sequence->prev->type;//exec is the type of the token before the command
		add_cmd_to_list(current_command, command_list);//adicina o comando a lista de comandos
		while (token_sequence)
		{
			if (token_sequence->type == AND
				|| token_sequence->type == OR)
			{
				(token_sequence) = (token_sequence)->next;
				break ;
			}
			else if (token_sequence->type == SMALLER
				|| token_sequence->type == HERE_DOC
				|| token_sequence->type == GREATER
				|| token_sequence->type == APPEND)
				process_redirection(&token_sequence, &current_command);
			// else if (token_sequence->type == OPEN_PAR)
			// 	handle_paranthesis(&token_sequence, &current_command);
			else if (token_sequence->type == STRING)
				add_argument(&token_sequence, &current_command);
			else if (token_sequence->type == PIPE)
			{
				current_command = create_next_command(&token_sequence, &current_command);
				add_cmd_to_list(current_command, command_list);//adicina o comando a lista de comandos
			}
		}
	}
	g_minishell.parsed = command_list;
	return (command_list);
}
