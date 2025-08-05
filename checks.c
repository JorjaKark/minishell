/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:05:26 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/05 17:31:47 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

int	ft_check_cmd(char **cmd)
{
	if (cmd[0] == NULL)
	{
		free_paths(cmd);
		return (1);
	}
	return (0);
}

void	ft_check_path(char *paths, char **cmd, t_minishell *mini)
{
	if (!paths)
	{
		error_mini('c', mini, cmd);
		mini->m_g_sig_num = 127;
		exit(127);
	}
}

void	ft_check_valid(char *valid_path, char **cmd, t_minishell *mini)
{
	if (!valid_path)
	{
		error_mini('c', mini, cmd);
		free(cmd);
	}
}
