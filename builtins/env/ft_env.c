/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:25:07 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 15:23:20 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(int argc, char ***env, t_minishell *mini)
{
	int	i;

	if (argc > 1)
	{
		arg_and_options_are_not_supported(mini);
		return ;
	}
	i = 0;
	if (*env == NULL)
		return ;
	while ((*env)[i])
	{
		printf("%s\n", (*env)[i]);
		i++;
	}
	mini->m_g_sig_num = 0;
	return ;
}
