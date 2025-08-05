/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafferre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:43:12 by mafferre          #+#    #+#             */
/*   Updated: 2024/08/25 20:43:14 by mafferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_letter(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	valid_arg(char *argv)
{
	int	j;

	if (argv[0] == '=')
		return (0);
	else if (!((argv[0] >= 'A' && argv[0] <= 'Z') || (argv[0] >= 'a'
				&& argv[0] <= 'z') || argv[0] == '_'))
		return (0);
	j = 1;
	while (argv[j] && argv[j] != '=' && argv[j] != '+')
	{
		if (!is_valid_letter(argv[j]))
			return (0);
		j++;
	}
	if (argv[j] && argv[j] == '=')
		return (1);
	else if (argv[j] && argv[j] == '+')
	{
		if (argv[j + 1] && argv[j + 1] == '=')
			return (2);
		else
			return (0);
	}
	return (3);
}

int	does_var_exist_export(char *var, char **copy_env)
{
	int		i;
	char	*equal_s;
	int		len;

	i = 0;
	while (copy_env[i] != NULL)
	{
		equal_s = ft_strchr(copy_env[i], '=');
		if (equal_s)
			len = equal_s - copy_env[i];
		else
			len = ft_strlen(var);
		if (ft_strncmp(copy_env[i], var, len) == 0 && ft_strlen(var) == len)
			return (1);
		i++;
	}
	return (0);
}

void	red_to_case(int disclaimer, char *argv, char ***env_copy)
{
	if (disclaimer == 2)
		concatenation(argv, env_copy);
	else
		no_equal_var(argv, env_copy);
}
