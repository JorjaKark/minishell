/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:07:32 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 15:24:20 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_letter_pwd(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

void	ft_pwd(int argc, char **argv, t_minishell *mini)
{
	int		i;
	char	cwd[4096];
	char	c;

	i = 0;
	if (argc > 1 && ft_strncmp(argv[1], "-", 1) == 0 && ft_strlen(argv[1]) > 1
		&& is_valid_letter_pwd(argv[1][1]))
	{
		options_are_not_supported_pwd(argv[1][1], mini);
		return ;
	}
	if (getcwd(cwd, 4096))
	{
		while (cwd[i])
		{
			c = cwd[i];
			write(1, &c, 1);
			i++;
		}
		write(1, "\n", 1);
	}
	mini->m_g_sig_num = 0;
	return ;
}
