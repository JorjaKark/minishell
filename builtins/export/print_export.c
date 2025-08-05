/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafferre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:44:34 by mafferre          #+#    #+#             */
/*   Updated: 2024/08/25 20:44:36 by mafferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export(char **env_copy)
{
	int	i;
	int	j;

	i = -1;
	env_sort(env_copy);
	while (env_copy[++i])
	{
		j = 0;
		printf("declare -x ");
		while (env_copy[i][j] && env_copy[i][j] != '=')
		{
			printf("%c", env_copy[i][j]);
			j++;
		}
		if (env_copy[i][j] == '=')
		{
			printf("=\"");
			j++;
			while (env_copy[i][j])
				printf("%c", env_copy[i][j++]);
			printf("\"");
		}
		printf("\n");
	}
}

void	env_sort(char **env_copy)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (env_copy[i])
	{
		j = i + 1;
		while (env_copy[j])
		{
			len = ft_strlen(env_copy[i]);
			if (ft_strncmp(env_copy[i], env_copy[j], len + 1) > 0)
				swap_strings(&env_copy[i], &env_copy[j]);
			j++;
		}
		i++;
	}
}

void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	make_it_valid(char **argv)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	str = *argv;
	if (str[0] && str[0] == '=')
		i = 0;
	while (str[++i])
	{
		str[j++] = str[i];
	}
	str[j] = '\0';
}
