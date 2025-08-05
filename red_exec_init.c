/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_exec_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:48 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/15 17:49:24 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_red(t_minishell *mini, int i, int num_pipes, int **pipes)
{
	int	j;

	signal(SIGINT, ctrlc_handler);
	if (mini->has_heredoc)
	{
		dup2(mini->heredoc_fd, STDIN_FILENO);
		close(mini->heredoc_fd);
	}
	else if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < num_pipes)
		dup2(pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < num_pipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	exec_n_built(t_tree *current_node, char **env, t_minishell *mini)
{
	if (current_node->cmd->name != NULL)
		execute(mini->cmd_arg, env, mini);
	else
		free_exit_n_cmd(mini);
	free_everything(mini);
	exit(0);
}

void	init_inicial_pp(t_minishell *mini)
{
	mini->pipes = malloc(1 * sizeof(int *));
	if (!mini->pipes)
		return ;
	mini->pids = malloc(1 * sizeof(pid_t));
	if (!mini->pids)
		return ;
}

void	free_i(t_minishell *mini)
{
	free(mini->pids);
	free(mini->pipes);
}

void	init_pipes_pids(t_minishell *mini)
{
	int	i;

	mini->flag_pipes = 1;
	mini->pipes = malloc(mini->num_pipes * sizeof(int *));
	if (!mini->pipes)
		return ;
	i = 0;
	while (i < mini->num_pipes)
	{
		mini->pipes[i] = malloc(2 * sizeof(int));
		if (!mini->pipes[i])
			return ;
		i++;
	}
	mini->pids = malloc((mini->num_pipes + 1) * sizeof(pid_t));
	if (!mini->pids)
		return ;
}
