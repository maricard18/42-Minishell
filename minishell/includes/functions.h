/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maricard <maricard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 22:10:59 by mariohenriq       #+#    #+#             */
/*   Updated: 2023/06/06 20:38:56 by maricard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//------------Main----------------//
void		minishell_init(char **env);
void		initialize_shell(char *str);
void		clean_all(char *str);

//----------Signals---------------//
void		ctrl_c(int signal);
void		ctrl_d(char *str);
//void		rl_replace_line(const char *text, int clear_undo);

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
t_parsed	**parse_commands(int in_file, int out_file,
				t_token *token_sequence);
int			validate_syntax(t_token *my_tokens);
void		handle_paranthesis(t_token **tokens_list, t_parsed **command);
void		skip_to_matching_parenthesis(t_token **command_token_list);
void		handle_paranthesis(t_token **tokens_list, t_parsed **command);
void		add_cmd_to_list(t_parsed *current_command, t_parsed **command_list);
t_parsed	*allocate_and_init_command(int in_file, int out_file);
int			count_and_or_tokens(t_token *command_token_list);
void		get_next_token(t_token *command_table);
int			token_counter(char **str);

//-------Execution---------------//
void		execution(void);
void		execute_execve(char **args);
void		execute_builtin_command(char **arguments);
int			get_builtin_type(char *command);
char		*ft_strtok(char *str, char delimeter);
void		redirect_in(t_parsed *temp, t_file *file);
void		redirect_out(t_parsed *temp, t_file *file);
void		append(t_parsed *temp, t_file *file);
void		here_doc(t_parsed *temp, char *name);
void		write_process(t_parsed *temp, int pipe_fd);
void		read_process(t_parsed *temp, int pipe_fd);
void		execute_commands(t_parsed *temp);
void		execve_or_builtin(char **args);
char		*ft_strjoin2(char const *s1, char const *s2);
int			**open_pipes(void);
void		close_pipes(int *pipe_fd);

//--------Commands---------------//
void		cd_command(char **input);
void		echo_command(char **input);
void		env_command(char **input);
void		exit_command(char **input);
void		pwd_command(void);
void		unset_command(char **input);
void		export_command(char **input);

//---------Utils-----------------//
void		update_path_directories(void);
int			number_args_env_var(void);
void		free_array(char **arr);
int			handle_error(int error_code, char *custom_message);
char		*ft_strcpy(char *dest, const char *src);
int 		ft_strclen(char *str, char c);

//---------Tests-----------------//
void		lexer_test(void);
void		parser_test(void);
char		*check_type(int type);

#endif