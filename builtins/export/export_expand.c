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

void	ft_expand_helper(char ***env_copy, char ***new_env_copy, int len)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		(*new_env_copy)[i] = ft_strdup((*env_copy)[i]);
		if (!(*new_env_copy)[i])
		{
			free_s_new(*new_env_copy);
			*new_env_copy = NULL;
			return ;
		}
		i++;
	}
}

void	ft_expand(char ***env_copy, int len, char *var)
{
	char	**new_env_copy;

	new_env_copy = (char **)malloc((len + 1) * sizeof(char *));
	if (!new_env_copy)
		return ;
	ft_expand_helper(env_copy, &new_env_copy, len);
	if (!new_env_copy)
		return ;
	new_env_copy[len - 1] = ft_strdup(var);
	if (!new_env_copy[len - 1])
	{
		free_s_new(new_env_copy);
		return ;
	}
	new_env_copy[len] = NULL;
	free_s_new(*env_copy);
	*env_copy = new_env_copy;
}
