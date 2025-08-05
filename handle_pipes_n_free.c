/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_n_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:03 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 17:58:32 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipes(t_minishell *mini, int num_pipes)
{
	int	i;

	init_pipes_pids(mini);
	ft_memset(mini->pids, 0, sizeof(pid_t) * (mini->num_pipes + 1));
	i = 0;
	mini->heredoc_fd = -1;
	mini->has_heredoc = 0;
	while (i < num_pipes)
	{
		if (pipe(mini->pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	mini->is_here = 0;
	mini->current_node = mini->tree;
}

int	check_here(t_minishell *mini, t_tree *current_node)
{
	mini->heredoc_fd = -1;
	mini->has_heredoc = 0;
	mini->redirection = current_node->red->red_op;
	mini->redirection_f = current_node->red->red_file;
	while (mini->redirection != NULL)
	{
		if (mini->redirection->subtype == RLESS && !mini->redirection->ambiguous)
		{
			if (mini->heredoc_fd != -1)
				close(mini->heredoc_fd);
			mini->heredoc_fd = handle_heredoc(mini->redirection,
					mini->redirection_f, mini);
			if (mini->heredoc_fd == -1)
				return (-1);
			mini->has_heredoc = 1;
		}
		else if(mini->redirection->subtype == RLESS && mini->redirection->ambiguous)
			write(2, "ambiguous redirect\n", 20);
		mini->redirection = mini->redirection->next;
		mini->redirection_f = mini->redirection_f->next;
	}
	return (0);
}

void	n_built(t_minishell *mini, int i, int **pipes, pid_t *pids)
{
	pids[i] = fork();
	if (pids[i] < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pids[i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		pipe_red(mini, i, mini->num_pipes, pipes);
		handle_red(mini->redirection, mini->redirection_f, mini,
			mini->current_node);
		exec_n_built(mini->current_node, mini->env_copy, mini);
	}
}

void	free_pipes_pids(t_minishell *mini)
{
	int	i;

	i = 0;
	if (mini->flag_pipes)
	{
		while (i < mini->num_pipes)
		{
			if (mini->pipes[i])
			{
				close(mini->pipes[i][0]);
				close(mini->pipes[i][1]);
				free(mini->pipes[i]);
			}
			mini->pipes[i] = NULL;
			i++;
		}
		free(mini->pipes);
		free(mini->pids);
	}
	mini->flag_pipes = 0;
}
