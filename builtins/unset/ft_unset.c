/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:13:57 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 15:24:59 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_letter_unset(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

void	free_s_unset(char **s)
{
	int	i;

	i = 0;
	if (!s)
	{
		free(s);
		return ;
	}
	while (s[i])
		free(s[i++]);
	free(s);
}

int	does_var_exist_unset(char *var, char **env_copy)
{
	int		i;
	char	*equal_s;
	int		len;

	i = 0;
	while (env_copy[i] != NULL)
	{
		equal_s = ft_strchr(env_copy[i], '=');
		if (equal_s)
		{
			len = equal_s - env_copy[i];
			if (ft_strncmp(env_copy[i], var, len) == 0 && ft_strlen(var) == len)
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	remove_env_var(char ***env_copy, char *var)
{
	int		i;
	int		j;
	int		var_len;
	char	**new_env;

	i = 0;
	j = 0;
	var_len = ft_strlen(var);
	while ((*env_copy)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return ;
	i = 0;
	while ((*env_copy)[i])
	{
		if (ft_strncmp((*env_copy)[i], var, var_len) != 0
			|| (*env_copy)[i][var_len] != '=')
			new_env[j++] = ft_strdup((*env_copy)[i]);
		i++;
	}
	new_env[j] = NULL;
	free_s_unset(*env_copy);
	*env_copy = new_env;
}

void	ft_unset(int argc, char **argv, char ***env_copy, t_minishell *mini)
{
	int	i;

	i = 1;
	if (argc == 1)
	{
		mini->m_g_sig_num = 0;	
		return ;
	}
	if (argc > 1 && ft_strncmp(argv[1], "-", 1) == 0 && ft_strlen(argv[1]) > 1
		&& is_valid_letter_unset(argv[1][1]))
	{
		options_are_not_supported_unset(argv[1][1], mini);
		return ;
	}
	while (i < argc)
	{
		if (does_var_exist_unset(argv[i], *env_copy))
		{
			remove_env_var(env_copy, argv[i]);
		}
		i++;
	}
	mini->m_g_sig_num = 0;
	return ;
}
