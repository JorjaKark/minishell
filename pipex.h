/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:15:38 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 17:20:13 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "builtins/builtins.h"
# include "libft/libft.h"
# include "parser.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// main.c
void		free_error2(t_minishell *mini);
void		free_other_arg(t_minishell *mini);
int			size_list(t_token *node);
char		**t_cmd_to_argv(t_tree *node);
void		parent(pid_t pid1, pid_t pid2, int *p_fd);
void		red_out(t_token *op, t_token *f, t_minishell *mini);
int			red_out_built(t_token *op, t_token *f, t_minishell *mini);
void		red_in(t_token *op, t_token *f, t_minishell *mini, int flag_here);
int			red_in_built(t_token *op, t_token *f,
				t_minishell *mini, int flag_here);
void		child1(t_tree *node, int *fd, char **env);
void		child2(t_tree *node, int *fd, char **env);
void		child_process(t_tree *node, int *input_fd, int *output_fd,
				char **env);
void		ft_builtin(int argc, char **cmd, t_minishell *mini);
int			is_builtin(char *cmd);
void		free_error(t_minishell *mini);
int			ft_strstrlen(char **str);
int			go_to_path(const char *path_type);
int			is_valid_number(char *arg);
void		ft_fprintf(char *str, char *str2);
void		free_token(t_token *token);
void		free_cmd(t_cmd *cmd);
void		free_pipes_pids(t_minishell *mini);

int			q_check(int *a, int *i, char *line, char quote);

int			check_quote(char *line);

t_token		*dup_token(t_token *token);

void		insert_at_end(t_token **head, t_token *new_token);

t_token		*create_token(char *value, int type, int subtype, int expand);

int			check_greats(t_token *tmp);
int			check_less(t_token *tmp);
int			check_op_pipe(t_token *tmp);
int			check_syntax(t_token *token);

void		free_tokens(t_token *token);
void		put_token(t_token **head, char *value, int expand, char *t);
int			is_between_quotes(char *line, int i);
void		add_s(char *line, char *new_line, int *i, int *j);
char		*add_space_op(char *line);

void		ft_fcalloc(char **str, int size);
int			ft_strstrlen(char **str);
char		*ft_strjoin_char(char *s, char c);
char		*ft_strsub(const char *s, unsigned int start, size_t len);
int			is_digit(char c);

void		op_add(t_temp *temp1, t_tree *node, t_token **temp);
void		cmd_add(int *flag, t_token **temp, t_tree *node, t_temp *temp1);
void		cmd_arg_2(t_token **temp, t_tree *node, t_temp *temp1);
t_tree		*init(void);
void		node_add(t_token **temp, t_tree *node, t_temp *temp1, int *flag);

void		free_token(t_token *token);
void		free_red(t_red *red);
void		free_cmd(t_cmd *cmd);
void		init_tree(t_tree **tree);
void		free_tree(t_tree *tree);

int			is_quote(char c);
char		*extract_var_name(const char *str);
void		insert_at_end_tree(t_tree **head, t_tree *new_token);
void		init_parser(t_tree *node, int *flag);
t_tree		*parse(t_token *token);

int			does_var_exist(const char *var_name, char **env);
int			env_count(char **env);
void		get_and_free(char **new_env, int i, char **var, char **value);
char		*get_env_value(const char *var_name, char **env);

char		*remove_quotes_old(char *split);
void		expand_n(t_expand *exp, char **env, int *flag, const char *str);
void		expand_e(t_expand *exp, t_minishell *mini);
void		init_exp(t_expand *exp);
char		*expand_var(const char *str, char **env,
				int *flag, t_minishell *mini);

char		**ft_strdupdup(char **s);
void		ign(char *new, t_counter *cnt);
void		advance(char **split, t_counter *cnt);
void		advance_quote(char **split, t_counter *cnt, char quote);
void		remove_q(char **split, t_counter *cnt,
				int *flag, t_minishell *mini);

char		**remove_loop(t_counter *cnt, char **split,
				char **env, t_minishell *mini);
t_counter	*remove_quotes(char **split, char **env, t_minishell *mini);
void		tokener(int *i, char **split, t_token **token, char **t);
void		free_s_d(char **split, int *i);

void		ctrlc_handler(int signum);
void		ctrlc_here(int signum);
void		free_node(t_minishell *mini);
void		free_here(t_minishell *mini);
void		fork_here(void);

int			wait_here(int *heredoc_pipe, int *signal_pipe, pid_t pid);
int			check_end(char *line, t_token *redirection_f);
void		line_loop(t_minishell *mini, t_token *redirection_f,
				int *heredoc_pipe, int *signal_pipe);
int			handle_heredoc(t_token *redirection, t_token *redirection_f,
				t_minishell *mini);

void		wait_p(int *pids, int num_pipes, t_minishell *mini);
void		close_p(int i, int **pipes, t_minishell *mini);
void		free_exit_n_cmd(t_minishell *mini);
void		handle_red(t_token *redirection, t_token *redirection_f,
				t_minishell *mini, t_tree *current_node);
int			handle_red_built(t_token *redirection, t_token *redirection_f,
				t_minishell *mini, t_tree *current_node);
void		built_main(t_token *redirection, t_token *redirection_f,
				t_minishell *mini, t_tree *current_node);
void		if_has_removed_var_nulls(int has_removed_var, char **result);
char		*start_len_name(char *str, int i[2], int *var_length);
int			variable_exists(const char *var, char **env);
void		init_pipex_main(t_minishell *mini, t_tree *current_node,
				int *is_builtin_cmd);
void		built_ready_here(t_minishell *mini);
void		built_dup(int i, int num_pipes, int **pipes, t_minishell *mini);
void		built_exec(t_minishell *mini, int i, int num_pipes, int **pipes);
void		init_pipex(t_tree *current_node, t_minishell *mini,
				int *is_builtin_cmd);
char		*r_nexist_var(char *str, char **env);
char		*ft_strndup(char *s, int n);
void		pipe_red(t_minishell *mini, int i, int num_pipes, int **pipes);

void		pipe_red(t_minishell *mini, int i, int num_pipes, int **pipes);
void		exec_n_built(t_tree *current_node, char **env, t_minishell *mini);
void		init_inicial_pp(t_minishell *mini);
void		free_i(t_minishell *mini);
void		init_pipes_pids(t_minishell *mini);
void		ft_strcpy(char *dst, char *src);
int			ft_strncpy(char *dst, char *src, int n);

void		init_pipes(t_minishell *mini, int num_pipes);
int			check_here(t_minishell *mini, t_tree *current_node);
void		built(t_minishell *mini, pid_t *pids, int *i, int **pipes);
void		n_built(t_minishell *mini, int i, int **pipes, pid_t *pids);
void		free_pipes_pids(t_minishell *mini);

int			checks(t_minishell *mini);
void		parse_exec(t_minishell *mini);
void		init_var_main(t_minishell *mini, char **env, int ac, char **av);
void		lex_parse_exec(t_minishell *mini);
void		free_if_b(t_minishell *mini);

t_token		*lexing(char *line, char **env, t_minishell *mini);
int			count_commands(t_tree *tree);
void		pipex_main(t_tree *tree, t_minishell *mini);

int			is_builtin(char *cmd);
int			to_argc(char **cmd);
int			is_absolute_path(char *path);
int			is_executable(const char *path);
char		**ft_str_arr_join(char *s1, char **s2);

int			is_binary_file(char *path);

void		e_execve(char *valid_path, char **cmd, char **env,
				t_minishell *mini);
void		e_execve_c(char *valid_path, char **cmd, char **env,
				t_minishell *mini);
void		exec_absolute(char *valid_path, char **cmd, char **env,
				t_minishell *mini);
void		executable_opt(char *valid_path, char **cmd, char **env,
				t_minishell *mini);
void		exec_executable(char *valid_path, char **cmd, char **env,
				t_minishell *mini);

int			size_list(t_token *node);
void		dup_value_curr_arg(t_token *current_arg, char ***argv, int *i);
char		**t_cmd_to_argv(t_tree *node);

void		ft_fprintf(char *str, char *str2);
void		free_error(t_minishell *mini);
void		free_and_exit(t_minishell *mini);
void		free_and_exit_built(t_minishell *mini);
void		fail_open_file(char *file, t_minishell *mini);

void		count_helper(char const *s, int c, int *a, int *count);
int			count_words(char const *s, char c);
void		check_alloc(int *i, int *value);
void		is_white(int **i, char const *s, int *a);
void		alloc_helper(int *i, int a, int *value, char const *s);

int			write_helper(char const *s, t_vars *var, char **strstr, int index);
void		write_words(char **strstr, char const *s, char c, int index);

void		error_inv_prem(char c);
void		error(char c);
void		free_other_arg(t_minishell *mini);

int			is_path(char *env);
char		*get_paths(char *env_paths, char *cmd);
void		path_env(char **env, char **paths);

// execute.c
int			is_path(char *env);
char		*get_paths(char *env_paths, char *cmd);

void		execute(char **cmd, char **env, t_minishell *mini);
char		**add_prog_to_array(char **original_array);
// utils.c

void		error_checkers(char c);
int			is_path_valid(char *path);
void		free_paths(char **paths);

// checks.c
void		ft_check_null(char **cmd);
int			ft_check_cmd(char **cmd);
void		ft_check_path(char *paths, char **cmd, t_minishell *mini);
void		ft_check_valid(char *valid_path, char **cmd, t_minishell *mini);

void		error(char c);
void		error_mini(char c, t_minishell *mini, char **cmd);
void		free_tree(t_tree *tree);
void		free_tokens(t_token *token);
void		free_everything(t_minishell *mini);
void		heredoc(t_token *op, t_token *f, t_minishell *mini);
void		free_node(t_minishell *mini);
void		free_cmd_arg(t_minishell *mini);

void		ft_builtin_exit(char **cmd, t_minishell *mini);
void		free_close_exit_built(t_minishell *mini);
void		built_first(t_minishell *mini, int *i, int **pipes);
int			handle_red_built(t_token *redirection, t_token *redirection_f,
				t_minishell *mini, t_tree *current_node);

int			check_if_heredoc_after(t_token *redirection, t_minishell *mini);
void		close_pipes(int *heredoc_pipe, int *signal_pipe);

#endif
