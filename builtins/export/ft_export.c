/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:36:36 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 15:34:18 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	update_var(char *var_name, char *var_value, char **var_arr,
		char ***env_copy)
{
	if (var_arr[1])
		put_valid_value(&var_value, var_arr);
	else
		put_null_var_value(&var_value);
	if (does_var_exist_export(var_name, *env_copy))
		var_exists_case(var_name, var_value, env_copy);
	else
		var_does_not_exist_case(var_name, var_value, env_copy);
	free(var_value);
	free_split(var_arr);
}

void	iterate_argv_helper(char *argv_k, char ***env_copy)
{
	char	**var_arr;
	char	*var_name;
	char	*var_value;

	var_arr = ft_split(argv_k, '=');
	if (var_arr)
	{
		var_name = var_arr[0];
		var_value = NULL;
		update_var(var_name, var_value, var_arr, env_copy);
	}
}

void	iterate_argv(char **argv, char ***env_copy, t_minishell *mini)
{
	int	k;

	k = 1;
	while (argv[k])
	{
		if (!valid_arg(argv[k]))
			not_a_valid_identifier(argv[k], mini);
		else if (valid_arg(argv[k]) == 1)
		{
			iterate_argv_helper(argv[k], env_copy);
			mini->m_g_sig_num = 0;
		}
		else
		{
			red_to_case(valid_arg(argv[k]), argv[k], env_copy);
			mini->m_g_sig_num = 0;
		}
		k++;
	}
}

void	ft_export(int argc, char **argv, char ***env_copy, t_minishell *mini)
{
	if (argc == 1)
	{
		print_export(*env_copy);
		mini->m_g_sig_num = 0;
		return ;
	}
	if (argc > 1 && ft_strncmp(argv[1], "-p", 2) == 0
		&& ft_strlen(argv[1]) == 2)
	{
		options_are_not_supported_export(argv[1], mini);
		return ;
	}
	else
		iterate_argv(argv, env_copy, mini);
}
