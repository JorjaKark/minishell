/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:39 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/05 17:31:42 by erferrei         ###   ########.fr       */
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

extern int	g_sig_num;

void	free_all(t_minishell *mini, char **cmd)
{
	free_everything(mini);
	free_s(cmd);
	if (mini->node)
	{
		free(mini->node->cmd);
		mini->node->cmd = NULL;
		free(mini->node->red);
		free(mini->node);
		mini->node = NULL;
	}
}

void	error_mini_p_a_e(char c, t_minishell *mini, char **cmd)
{
	if (c == 'p')
	{
		ft_fprintf(cmd[0], "Permission denied\n");
		free_all(mini, cmd);
		mini->m_g_sig_num = 126;
		exit(126);
	}
	else if (c == 'a')
	{
		write(STDERR_FILENO, "Error: Invalid argument\n", 24);
		free_all(mini, cmd);
		mini->m_g_sig_num = 128;
		exit(128);
	}
	else if (c == 'e')
	{
		write(STDERR_FILENO, "exit\n", 5);
		free_all(mini, cmd);
		mini->m_g_sig_num = 2;
		exit(2);
	}
}

void	print_cmd_not_found(char **cmd)
{
	if (cmd[0][0] == 0)
		write(2, "Command \'\' not found\n", 21);
	else
		ft_fprintf(cmd[0], "command not found\n");
}

void	error_mini(char c, t_minishell *mini, char **cmd)
{
	if (c == 'c')
	{
		print_cmd_not_found(cmd);
		free_other_arg(mini);
		free_all(mini, cmd);
		mini->m_g_sig_num = 127;
		exit(127);
	}
	else if (c == 'f')
	{
		ft_fprintf(cmd[0], "No such file or directory\n");
		free_all(mini, cmd);
		mini->m_g_sig_num = 127;
		exit(127);
	}
	else if (c == 'z')
	{
		mini->m_g_sig_num = 130;
		return ;
	}
	error_mini_p_a_e(c, mini, cmd);
	mini->m_g_sig_num = 1;
	free_all(mini, cmd);
	exit(1);
}
