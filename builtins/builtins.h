/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:41:57 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/05 18:12:09 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../parser.h"
# include "../pipex.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_echo
{
	int	i;
	int	flag;
}		t_echo;

// CD

// ft_cd.c
void	ft_cd(int argc, char **argv, char ***env_copy, t_minishell *mini);
void	too_points_case(char ***env_copy, t_minishell *mini);
char	*ft_last_dir(char *pwd);
void	go_to_path_cd(char *path_type, char ***env_copy);

// cd_erros.c
void	to_many_arguments(t_minishell *mini);
void	no_such_file_or_directory(char **argv, t_minishell *mini);
void	impossible_to_execute(t_minishell *mini);

// cd_utils.c
int		get_paths_len(char **paths);
void	ptr_to_last(char **ptr, char **paths, int i);
char	*create_last(char **paths);
char	**copy_env(char **env_copy, int new_size);
char	*get_env_var(char **env_copy, char *var);

// cd.free.c
void	free_env(char **env_copy);
void	free_paths_cd(char **paths);

// cd_pwd_oldpwd.c
char	*var_plus_value(char *var, char *value);
int		add_env_var(char ***env_copy, char *new_var);
int		replace_env_var(char **env_copy, char *var, char *new_var);
int		update_env_var(char ***env_copy, char *var, char *value);
void	update_pwd(char ***env_copy);

// ECHO

// ft_echo.c
void	ft_echo(int argc, char **argv);
int		is_n_edge_case(char **str);
int		is_tilde_edge_case(char **argv);
void	echo_print(int argc, char **argv, t_echo params);

// ENV

// ft_env.c
void	ft_env(int argc, char ***env, t_minishell *mini);

// env_errors.c
void	arg_and_options_are_not_supported(t_minishell *mini);

// EXIT

// ft_exit.c
void	ft_exit(int argc, char **argv, t_minishell *mini);
int		is_valid_number(char *arg);
void	free_exit(t_minishell *mini, char **cmd);
void	exit_directions(int argc, char **argv, t_minishell *mini);

// exit_errors.c
void	numeric_arguments_required(char **argv, t_minishell *mini);
void	too_many_arguments(t_minishell *mini);

// EXPORT

// ft_export.c
void	ft_export(int argc, char **argv, char ***env_copy, t_minishell *mini);
void	iterate_argv_helper(char *argv_k, char ***env_copy);
void	iterate_argv(char **argv, char ***env_copy, t_minishell *mini);
void	update_var(char *var_name, char *var_value, char **var_arr,
			char ***env_copy);

// export_errors.c
void	options_are_not_supported_export(char *argv, t_minishell *mini);
void	not_a_valid_identifier(char *argv, t_minishell *mini);

// export_no=.c
void	var_does_not_exist_case_no_equal(char *var_name, char ***env_copy);
void	no_equal_var(char *argv, char ***env_copy);

// export_utils.c
void	free_split(char **split_arr);
void	free_export(char *new_var_equal, char *new_var_total, int i,
			char ***env_copy);
void	free_s_new(char **s);
void	put_null_var_value(char **var_value);
void	put_valid_value(char **var_value, char **var_arr);

// export_var_cases.c
void	var_exists_case_helper(char *var_name, char *var_value,
			char **new_var_total);
void	var_exists_case(char *var_name, char *var_value, char ***env_copy);
void	var_does_not_exist_case(char *var_name, char *var_value,
			char ***env_copy);

// export+=.c
void	var_exists_case_concatenation_helper1(char *var_name, char *var_value,
			char ***env_copy, int i);
void	var_exists_case_concatenation_helper2(char *var_name, char *var_value,
			char ***env_copy, int i);
void	var_exists_case_concatenation(char *var_name, char *var_value,
			char ***env_copy);
void	concatenation(char *argv, char ***env_copy);

// checking_export.c
int		is_valid_letter(char c);
int		valid_arg(char *argv);
int		does_var_exist_export(char *var, char **copy_env);
void	red_to_case(int disclaimer, char *argv, char ***env_copy);

// print_export.c
void	print_export(char **env_copy);
void	env_sort(char **env_copy);
void	swap_strings(char **a, char **b);
void	make_it_valid(char **argv);

// export_expand.c
void	ft_expand_helper(char ***env_copy, char ***new_env_copy, int len);
void	ft_expand(char ***env_copy, int len, char *var);

// PWD

// ft_pwd.c
void	ft_pwd(int argc, char **argv, t_minishell *mini);
int		is_valid_letter_pwd(char c);

// pwd_errors.c
void	options_are_not_supported_pwd(char argv, t_minishell *mini);

// UNSET

// ft_unset.c
void	ft_unset(int argc, char **argv, char ***env_copy, t_minishell *mini);
void	remove_env_var(char ***env_copy, char *var);
int		does_var_exist_unset(char *var, char **env_copy);
void	free_s_unset(char **s);

// unset_errors.c
void	options_are_not_supported_unset(char argv, t_minishell *mini);

#endif
