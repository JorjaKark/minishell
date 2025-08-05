/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:47:48 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 18:22:13 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_builtin_exit(char **cmd, t_minishell *mini)
{
	if (!ft_strncmp(cmd[0], "exit", 5))
	{
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
}

void	free_close_exit_built(t_minishell *mini)
{
	int	j;

	free_error2(mini);
	j = 0;
	if (mini->line)
		free(mini->line);
	if (mini->token)
		free_tokens(mini->token);
	free_s(mini->env_copy);
	free_pipes_pids(mini);
	if (mini->flag_pipes)
	{
		while (j < mini->num_pipes)
		{
			close(mini->pipes[j++][0]);
			j++;
		}
	}
	exit(mini->m_g_sig_num);
}

void	built_first(t_minishell *mini, int *i, int **pipes)
{
	mini->saved_stdin = dup(STDIN_FILENO);
	mini->saved_stdout = dup(STDOUT_FILENO);
	built_dup(*i, mini->num_pipes, pipes, mini);
	if (handle_red_built(mini->redirection, mini->redirection_f, mini,
			mini->current_node) == 1)
		return ;
	if (!ft_strncmp(mini->cmd_arg[0], "exit", 5))
		printf("exit\n");
	built_exec(mini, *i, mini->num_pipes, pipes);
	if (mini->m_g_sig_num != 0 && mini->m_g_sig_num != -128)
		mini->m_g_sig_num -= 128;
}

void	built(t_minishell *mini, pid_t *pids, int *i, int **pipes)
{
	if (*i == 0)
		built_first(mini, i, pipes);
	else
	{
		pids[*i] = fork();
		if (pids[*i] < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pids[*i] == 0)
		{
			mini->saved_stdin = dup(STDIN_FILENO);
			mini->saved_stdout = dup(STDOUT_FILENO);
			built_dup(*i, mini->num_pipes, pipes, mini);
			if (handle_red_built(mini->redirection, mini->redirection_f, mini,
					mini->current_node) == 1)
			{
				mini->m_g_sig_num -= 128;
				free_close_exit_built(mini);
				return ;
			}	
			built_exec(mini, *i, mini->num_pipes, pipes);
			free_close_exit_built(mini);
		}
	}
}

int	handle_red_built(t_token *redirection, t_token *redirection_f,
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
			if (red_in_built(redirection, redirection_f, mini, here_flag) == 1)
				return (1);
		}
		else if (redirection->subtype == GREAT
			|| redirection->subtype == RGREAT)
		{
			if (red_out_built(redirection, redirection_f, mini) == 1)
				return (1);
		}
		redirection = redirection->next;
		redirection_f = redirection_f->next;
	}
	return (0);
}
