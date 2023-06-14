/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 22:10:59 by mariohenriq       #+#    #+#             */
/*   Updated: 2023/06/14 15:20:17 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"

//------------Main----------------//
void		minishell_init(char **env);
void		initialize_shell(char *str);

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
void		modify_string(char **old_str, char **new_str);
char		*single_quotes(char *input, int *i);
char		*double_quotes(char **env, char *input, int *i);
char		*handle_env_variables(char **env, char *str, int *i);
int			check_unfinished_quotes(char **str);
char		*search_expansions(char **env, char *str);
int			ft_strlen_special(char *str);

//--------Tokeniser---------------//
int			is_whitespace(char c);
void		special_chars(char *str, int k, t_token *token);
int			ft_strchr2(const char *s, char c);
int			check_for_redirect_in(char *str, t_token *token);
int			check_for_redirect_out(char *str, t_token *token);
int			check_for_pipes(char *str, t_token *token);
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
void		redirect_in(t_parsed *temp, t_file **file, t_fd **fd);
void		redirect_out(t_parsed *temp, t_file **file, t_fd **fd);
void		append(t_parsed *temp, t_file **file, t_fd **fd);
void		here_doc(t_parsed *temp, t_file **file, t_fd **fd);
void		execute_commands(t_parsed *temp, t_file *file, t_fd **fd);
void		execve_or_builtin(char **args);
char		*ft_strjoin2(char const *s1, char const *s2);
int			**open_pipes(void);
int			check_next_node(t_file **file);
void		write_here_doc(int pipe_fd, char *str);
char		*env_var(char *env, int i);
char		*my_get_env(char **env, char *str);
int			check_if_path(char *str);
void		sigint_handler(int signum);
void		duplicate_fds(void);

//--------Commands---------------//
void		cd_command(char **input);
void		echo_command(char **input);
void		env_command(char **input);
void		exit_command(char **input);
void		pwd_command(void);
void		unset_command(char **input);
void		export_command(char **input);
void		sort_env_variables(char **env);
void		export_print_all(void);
void		sort_and_print(void);
int			check_for_equal_sign(char *str, int *error);
int			check_while_n(char **input, int *i, int *a);
void		here_doc_handler(t_parsed *temp, t_file **file, t_fd **fd);
int			is_include(char *str);

//---------Utils-----------------//
void		update_path_directories(void);
int			number_args_env_var(void);
int			handle_error(int error_code, char *custom_message);
char		*ft_strcpy(char *dest, const char *src);
int			ft_strclen(char *str, char c);
void		print_error(char *arg, char *message, int exit_status);
int			ft_strchr3(const char *s, char c);
char		*get_env(char *var_name);
int			check_for_quotes(int k, t_token *token);

//---------Clean----------------//
void		clean_fd_list(t_fd *fd);
void		clean_all(char *str);
void		clean_the_mess(void);
void		free_open_pipes(int **pipe);
void		free_array(char **arr);

//---------Tests-----------------//
void		lexer_test(void);
void		parser_test(void);
char		*check_type(int type);

#endif