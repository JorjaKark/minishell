/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_opts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:44 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/15 17:46:36 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	e_execve(char *valid_path, char **cmd, char **env, t_minishell *mini)
{
	int	flag;

	if (execve(valid_path, cmd, env) == -1)
	{
		flag = 0;
		if (cmd[1] == NULL)
			flag = 1;
		free(valid_path);
		if (flag)
		{
			error_mini('f', mini, cmd);
			free(cmd);
		}
		free_paths(cmd);
		exit(EXIT_FAILURE);
	}
}

void	e_execve_c(char *valid_path, char **cmd, char **env, t_minishell *mini)
{
	int	flag;

	if (execve(valid_path, cmd, env) == -1)
	{
		flag = 0;
		if (cmd[1] == NULL)
			flag = 1;
		free(valid_path);
		if (flag)
		{
			error_mini('c', mini, cmd);
			free(cmd);
		}
		free_paths(cmd);
		exit(EXIT_FAILURE);
	}
}

void	exec_absolute(char *valid_path, char **cmd, char **env,
		t_minishell *mini)
{
	valid_path = ft_strdup(cmd[0]);
	ft_check_valid(valid_path, cmd, mini);
	e_execve(valid_path, cmd, env, mini);
}

void	executable_opt(char *valid_path, char **cmd, char **env,
		t_minishell *mini)
{
	int	flag;

	valid_path = ft_strdup(cmd[0]);
	cmd = ft_str_arr_join("/bin/bash", cmd);
	ft_check_valid(valid_path, cmd, mini);
	if (is_binary_file(valid_path) == 1)
		e_execve(valid_path, cmd, env, mini);
	if (execve("/bin/bash", cmd, env) == -1)
	{
		flag = 0;
		if (cmd[1] == NULL)
			flag = 1;
		free(valid_path);
		if (flag)
		{
			error_mini('c', mini, cmd);
			free(cmd);
		}
		free_paths(cmd);
		exit(EXIT_FAILURE);
	}
}

void	exec_executable(char *valid_path, char **cmd, char **env,
		t_minishell *mini)
{
	int	is_e;

	is_e = is_executable(cmd[0]);
	if (is_e == 1)
		executable_opt(valid_path, cmd, env, mini);
	else if (is_e == 2)
		error_mini('p', mini, cmd);
	else
		error_mini('f', mini, cmd);
}
