/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:35 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/05 17:30:41 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

void	free_other_arg(t_minishell *mini)
{
	t_tree	*temp;
	t_token	*temp1;

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
				if (mini->tree->cmd->args->value)
					free(mini->tree->cmd->args->value);
				mini->tree->cmd->args = mini->tree->cmd->args->next;
				free(temp1);
			}
			mini->tree = mini->tree->next;
		}
		mini->tree = temp;
	}
}
