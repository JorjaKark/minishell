/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:42:04 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/05 18:09:27 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int	g_sig_num;

void	options_are_not_supported_export(char *argv, t_minishell *mini)
{
	write(2, "export: '", 9);
	write(2, argv, ft_strlen(argv));
	write(2, "': options are not supported\n", 29);
	mini->m_g_sig_num = 1;
	return ;
}

void	not_a_valid_identifier(char *argv, t_minishell *mini)
{
	write(2, "export: `", 9);
	write(2, argv, ft_strlen(argv));
	write(2, "': not a valid identifier\n", 27);
	mini->m_g_sig_num = 1;
	return ;
}
