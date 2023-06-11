/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariohenriques <mariohenriques@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 22:10:59 by mariohenriq       #+#    #+#             */
/*   Updated: 2023/06/11 11:45:57 by mariohenriq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"

//------------Main----------------//
void		minishell_init(char **env);
void		initialize_shell(char *str);
void		clean_all(char *str);
void		clean_the_mess(void);
void		free_open_pipes(int **pipe);

//----------Signals---------------//
void		ctrl_c(int signal);
void		ctrl_d(char *str);

//-----------Lexer----------------//
void		lexer(char *str);
int			skip_quotes(char *str, int i);
int			count_tokens2(char *str, int i);
int			store_values2(char *str, int i);
void		search_env_vars(char **str);
char		*ft_char_string(char c);
void		modify_string(char **str, char *new_str);
char		*single_quotes(char *input, int *i);
char		*double_quotes(char **env, char *input, int *i);
char		*handle_env_variables(char **env, char *str, int *i);
int			check_unfinished_quotes(char **str);
char		*search_expansions(char **env, char *str);

//--------Tokeniser---------------//
int			is_whitespace(char c);
int			is_string(char *str);
void		special_chars(char *str, t_token *token);
int			ft_strchr2(const char *s, char c);
int			ft_strchr3(const char *s, char c, char d);
int			ft_strchr4(const char *s, char c);
void		check_for_redirect_in(char *str, t_token *token);
void		check_for_redirect_out(char *str, t_token *token);
void		check_for_pipes(char *str, t_token *token);
void		check_for_string(char *str, t_token *token);
void		check_for_(char *str, t_token *token);
void		check_for_parentheses(char *str, t_token *token);
void		check_for_and(char *str, t_token *token);
void		tokeniser(char **str);

//---------Parser-----------------//
void		parse_commands(int in_file, int out_file, t_token *token);
int			validate_syntax(t_token *my_tokens);
void		handle_paranthesis(t_token **tokens_list, t_parsed **command);
void		skip_to_matching_parenthesis(t_token **command_token_list);
void		handle_paranthesis(t_token **tokens_list, t_parsed **command);
void		add_cmd_to_list(t_parsed *current_command, t_parsed **command_list);
t_parsed	*init_command(int in_file, int out_file);
int			count_and_or_tokens(t_token *command_token_list);
void		get_next_token(t_token *command_table);
int			token_counter(char **str);

//-------Execution---------------//
void		execution(void);
void		execute_execve(char **args);
void		execute_builtin_command(char **arguments);
int			get_builtin_type(char *command);
char		*ft_strtok(char *str, char delimeter);
void		redirect_in(t_parsed *temp, t_file **file);
void		redirect_out(t_parsed *temp, t_file **file);
void		append(t_parsed *temp, t_file **file);
void		here_doc(t_parsed *temp, t_file **file);
void		write_process(t_parsed *temp, int pipe_fd);
void		read_process(t_parsed *temp, int pipe_fd);
void		execute_commands(t_parsed *temp, t_file *file);
void		execve_or_builtin(char **args);
char		*ft_strjoin2(char const *s1, char const *s2);
int			**open_pipes(void);
void		return_fds(void);
int			check_next_node(t_file **file);
void		write_here_doc(int pipe_fd, char *str);
char		*env_var(char *env, int i);
char		*my_get_env(char **env, char *str);
int			check_if_path(char *str);
void		sigint_handler(int signum);

//--------Commands---------------//
void		cd_command(char **input);
void		echo_command(char **input);
void		env_command(char **input);
void		exit_command(char **input);
void		pwd_command(void);
void		unset_command(char **input);
void		export_command(char **input);
void		sort_env_variables(char **env);

//---------Utils-----------------//
void		update_path_directories(void);
int			number_args_env_var(void);
void		free_array(char **arr);
int			handle_error(int error_code, char *custom_message);
char		*ft_strcpy(char *dest, const char *src);
int			ft_strclen(char *str, char c);
void		print_error(char *arg, char *message, int exit_status);

//---------Tests-----------------//
void		lexer_test(void);
void		parser_test(void);
char		*check_type(int type);

#endif