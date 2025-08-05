/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:35:59 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/15 18:10:28 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

int	checks(t_minishell *mini)
{
	if (mini->line == NULL)
	{
		printf("exit\n");
		return (1);
	}
	if (!mini->line)
		return (1);
	if (check_quote(mini->line))
	{
		printf("quote error\n");
		add_history(mini->line);
		mini->m_g_sig_num = 2;
		return (2);
	}
	return (0);
}

void	parse_exec(t_minishell *mini)
{
	mini->tree = parse(mini->token);
	mini->num_pipes = count_commands(mini->tree) - 1;
	if (mini->num_pipes == -1)
		mini->num_pipes = 0;
	pipex_main(mini->tree, mini);
}
