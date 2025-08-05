/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:36 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 18:22:00 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

void	wait_p(int *pids, int num_pipes, t_minishell *mini)
{
	int	status;
	int	i;

	(void)mini;
	status = 0;
	i = 0;
	while (i <= num_pipes)
	{
		if (waitpid(pids[i], &status, 0) > 0)
		{
			if (WIFEXITED(status))
				mini->m_g_sig_num = WEXITSTATUS(status) - 128;
			else if (WIFSIGNALED(status))
			{
				g_sig_num = WTERMSIG(status);
				if (g_sig_num == 2)
					printf("\n");
				if (g_sig_num == 3)
					printf("Quit (core dumped)\n");
			}
		}
		i++;
	}
	signal(SIGINT, ctrlc_handler);
}

void	close_p(int i, int **pipes, t_minishell *mini)
{
	if (i > 0)
	{
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
	}
	if (mini->has_heredoc)
		close(mini->heredoc_fd);
}

void	free_exit_n_cmd(t_minishell *mini)
{
	mini->m_g_sig_num = 0;
	if (mini->node)
	{
		free(mini->node->cmd);
		free(mini->node->red);
		free(mini->node);
		mini->node = NULL;
	}
	free_s(mini->cmd_arg);
	mini->cmd_arg = NULL;
	free_everything(mini);
	exit(mini->m_g_sig_num);
}

int	check_if_heredoc_after(t_token *redirection, t_minishell *mini)
{
	t_token	*tmp;

	tmp = redirection;
	if (mini->has_heredoc)
	{
		while (tmp->next != NULL)
		{
			if (tmp->next->subtype == RLESS)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

void	handle_red(t_token *redirection, t_token *redirection_f,
		t_minishell *mini, t_tree *current_node)
{
	int		here_flag;

	redirection = current_node->red->red_op;
	redirection_f = current_node->red->red_file;
	while (redirection != NULL)
	{
		here_flag = check_if_heredoc_after(redirection, mini);
		if (redirection->subtype == LESS)
		{
			red_in(redirection, redirection_f, mini, here_flag);
		}
		else if (redirection->subtype == GREAT
			|| redirection->subtype == RGREAT)
			{
				red_out(redirection, redirection_f, mini);
			}
		redirection = redirection->next;
		redirection_f = redirection_f->next;
	}
}
