/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:22 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/15 11:47:44 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex_main(t_minishell *mini, t_tree *current_node,
		int *is_builtin_cmd)
{
	if (current_node->cmd->name != NULL)
	{
		if (mini->cmd_arg != NULL)
		{
			free_s(mini->cmd_arg);
			mini->cmd_arg = NULL;
		}
		mini->cmd_arg = t_cmd_to_argv(current_node);
		*is_builtin_cmd = is_builtin(mini->cmd_arg[0]);
		mini->is_here = *is_builtin_cmd;
	}
}

void	built_ready_here(t_minishell *mini)
{
	if (mini->has_heredoc)
	{
		dup2(mini->heredoc_fd, STDIN_FILENO);
		close(mini->heredoc_fd);
	}
}

void	built_dup(int i, int num_pipes, int **pipes, t_minishell *mini)
{
	if (mini->has_heredoc)
	{
		dup2(mini->heredoc_fd, STDIN_FILENO);
		close(mini->heredoc_fd);
	}
	else if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < num_pipes)
		dup2(pipes[i][1], STDOUT_FILENO);
}

void	built_exec(t_minishell *mini, int i, int num_pipes, int **pipes)
{
	execute(mini->cmd_arg, mini->env_copy, mini);
	dup2(mini->saved_stdin, STDIN_FILENO);
	dup2(mini->saved_stdout, STDOUT_FILENO);
	close(mini->saved_stdin);
	close(mini->saved_stdout);
	if (i > 0)
		close(pipes[i - 1][0]);
	if (i < num_pipes)
		close(pipes[i][1]);
}

void	init_pipex(t_tree *current_node, t_minishell *mini, int *is_builtin_cmd)
{
	if (current_node->cmd->name != NULL)
	{
		if (mini->cmd_arg != NULL)
		{
			free_s(mini->cmd_arg);
			mini->cmd_arg = NULL;
		}
		mini->cmd_arg = t_cmd_to_argv(current_node);
		*is_builtin_cmd = is_builtin(mini->cmd_arg[0]);
		mini->is_here = *is_builtin_cmd;
	}
}
