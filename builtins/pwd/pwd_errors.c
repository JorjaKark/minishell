/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:07:46 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/05 18:11:41 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int	g_sig_num;

void	options_are_not_supported_pwd(char argv, t_minishell *mini)
{
	write(2, "pwd: `-", 7);
	write(2, &argv, 1);
	write(2, "': options are not supported\n", 29);
	mini->m_g_sig_num = 2;
	return ;
}
