/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:26:15 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 15:18:01 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int	g_sig_num;

int	is_valid_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == ' ')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while ((arg[i] >= '0' && arg[i] <= '9'))
	{
		i++;
	}
	if (arg[i])
		return (0);
	return (1);
}

void	free_exit(t_minishell *mini, char **cmd)
{
	free_other_arg(mini);
	free_everything(mini);
	free_s(cmd);
	if (mini->node)
	{
		free(mini->node->cmd);
		free(mini->node->red);
		free(mini->node);
		mini->node = NULL;
	}
}

void	exit_directions(int argc, char **argv, t_minishell *mini)
{
	if (argc == 1)
	{
		//mini->m_g_sig_num = 0;
		free_exit(mini, argv);
		close(mini->saved_stdin);
		close(mini->saved_stdout);
		if (mini->m_g_sig_num == 0)
			exit(0);
		exit(mini->m_g_sig_num - 128);
	}
	else if (argc > 1 && !is_valid_number(argv[1]))
	{
		numeric_arguments_required(argv, mini);
		free_exit(mini, argv);
		close(mini->saved_stdin);
		close(mini->saved_stdout);
		if (mini->m_g_sig_num == 0)
			exit(0);
		exit(mini->m_g_sig_num - 128);
	}
	else
		too_many_arguments(mini);
	return ;
}

void	ft_exit(int argc, char **argv, t_minishell *mini)
{
	int	nmr;

	nmr = 0;
	if (argc == 2 && is_valid_number(argv[1]))
	{
		nmr = ft_atoi(argv[1]);
		if (nmr > 255)
			nmr %= 256;
		else if (nmr < 0)
		{
			nmr = nmr * -1;
			nmr = 256 - (nmr % 256);
		}
		mini->m_g_sig_num = nmr;
		free_exit(mini, argv);
		close(mini->saved_stdin);
		close(mini->saved_stdout);
		if (mini->m_g_sig_num == 0)
			exit(0);
		exit(mini->m_g_sig_num - 128);
	}
	else
		exit_directions(argc, argv, mini);
	return ;
}
