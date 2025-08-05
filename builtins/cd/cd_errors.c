/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:42:07 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/05 18:01:03 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int	g_sig_num;

void	impossible_to_execute(t_minishell *mini)
{
	write(2, "cd: impossible to execute\n", 26);
	mini->m_g_sig_num = 1;
	return ;
}

void	no_such_file_or_directory(char **argv, t_minishell *mini)
{
	write(2, "cd: ", 4);
	write(2, argv[1], ft_strlen(argv[1]));
	write(2, ": No such file or directory\n", 28);
	mini->m_g_sig_num = 1;
	return ;
}

void	to_many_arguments(t_minishell *mini)
{
	write(2, "cd: too many arguments\n", 23);
	mini->m_g_sig_num = 1;
	return ;
}
