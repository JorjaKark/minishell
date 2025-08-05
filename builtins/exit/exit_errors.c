/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:46:16 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 15:20:44 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int	g_sig_num;

void	numeric_arguments_required(char **argv, t_minishell *mini)
{
	write(2, "exit: ", 6);
	write(2, argv[1], ft_strlen(argv[1]));
	write(2, ": numeric argument required\n", 29);
	mini->m_g_sig_num = 2 - 128;
	return ;
}

void	too_many_arguments(t_minishell *mini)
{
	write(2, "exit: too many arguments\n", 25);
	mini->m_g_sig_num = 1 - 128;
	return ;
}
