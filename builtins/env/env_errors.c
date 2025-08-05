/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:07:50 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/05 18:04:05 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int	g_sig_num;

void	arg_and_options_are_not_supported(t_minishell *mini)
{
	write(2, "env: arguments and options are not supported\n", 45);
	mini->m_g_sig_num = 1;
	return ;
}
