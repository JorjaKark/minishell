/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:33 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/10 19:23:33 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

void	ft_fprintf(char *str, char *str2)
{
	char	error_msg[256];
	int		len;
	int		i;

	len = 0;
	while (str[len] != '\0')
	{
		error_msg[len] = str[len];
		len++;
	}
	error_msg[len++] = ':';
	error_msg[len++] = ' ';
	i = 0;
	while (str2[i] != '\0')
	{
		error_msg[len++] = str2[i++];
	}
	write(STDERR_FILENO, error_msg, len);
}

void	free_error(t_minishell *mini)
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
				if (mini->tree->cmd->args->value)
					free(mini->tree->cmd->args->value);
				mini->tree->cmd->args = mini->tree->cmd->args->next;
				free(temp1);
			}
			mini->tree = mini->tree->next;
		}
		mini->tree = temp;
	}
	free_cmd_arg(mini);
	free_everything(mini);
}

void	free_and_exit(t_minishell *mini)
{
	mini->m_g_sig_num = 1;
	free_error(mini);
	exit(1);
}

void	free_and_exit_built(t_minishell *mini)
{
	mini->m_g_sig_num = 1;
	free_error(mini);
}

void	fail_open_file(char *file, t_minishell *mini)
{
	ft_fprintf(file, "Failed to open the file\n");
	free_and_exit(mini);
}
