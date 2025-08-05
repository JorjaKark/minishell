/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_n_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:55 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/05 19:00:00 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

void	ctrlc_handler(int signum)
{
	(void)signum;
	g_sig_num = 2;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\nminishell> ");
	return ;
}

void	ctrlc_here(int signum)
{
	char	*argv[2];
	char	*envp[1];
	int		i;

	(void)signum;
	g_sig_num = 2;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\n");
	g_sig_num = 2;
	argv[0] = "./sigint_sender";
	argv[1] = NULL;
	envp[0] = NULL;
	i = execve(argv[0], argv, envp);
	if (i == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(g_sig_num + 128);
	return ;
}

void	free_node(t_minishell *mini)
{
	if (mini->node)
	{
		free(mini->node->cmd);
		free(mini->node->red);
		free(mini->node);
		mini->node = NULL;
	}
}

void	free_here(t_minishell *mini)
{
	t_tree	*temp;
	t_token	*temp1;

	temp = mini->tree;
	temp1 = mini->tree->cmd->args;
	free_node(mini);
	while (mini->tree)
	{
		while (mini->tree->cmd->args)
		{
			temp1 = mini->tree->cmd->args;
			free(mini->tree->cmd->args->value);
			mini->tree->cmd->args = mini->tree->cmd->args->next;
			free(temp1);
		}
		mini->tree = mini->tree->next;
	}
	mini->tree = temp;
	if (mini->cmd_arg)
	{
		free_s(mini->cmd_arg);
		mini->cmd_arg = NULL;
	}
	free_everything(mini);
}

void	fork_here(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
