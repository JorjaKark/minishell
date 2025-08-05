/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:25 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 16:58:25 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "pipex.h"
#include "token.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int			g_sig_num;

void	free_cmd_arg(t_minishell *mini)
{
	if (mini->cmd_arg)
	{
		free_s(mini->cmd_arg);
		mini->cmd_arg = NULL;
	}
}

void	free_error2(t_minishell *mini)
{
	t_tree	*temp;
	t_token	*temp1;

	free_node(mini);
	temp = mini->tree;
	if (mini->tree)
	{
		temp1 = mini->tree->cmd->args;
		while (mini->tree)
		{
			while (mini->tree->cmd->args)
			{
				temp1 = mini->tree->cmd->args;
				free(mini->tree->cmd->args->old_expd);
				free(mini->tree->cmd->args->value);
				mini->tree->cmd->args = mini->tree->cmd->args->next;
				free(temp1);
			}
			mini->tree = mini->tree->next;
		}
		mini->tree = temp;
	}
	free_cmd_arg(mini);
	if (mini->tree)
		free_tree(mini->tree);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	mini;
	int			is_break;

	init_var_main(&mini, env, ac, av);
	while (1)
	{
		signal(SIGTSTP, SIG_IGN);
		signal(SIGINT, ctrlc_handler);
		signal(SIGQUIT, SIG_IGN);
		mini.line = readline("minishell> ");
		is_break = checks(&mini);
		if (is_break == 1)
			break ;
		else if (is_break == 0)
		{
			lex_parse_exec(&mini);
			add_history(mini.line);
			free_if_b(&mini);
		}
		free_pipes_pids(&mini);
	}
	free_node(&mini);
	free_s(mini.env_copy);
	exit(mini.m_g_sig_num - 128);
	return (0);
}
