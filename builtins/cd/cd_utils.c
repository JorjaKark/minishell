/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafferre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:41:36 by mafferre          #+#    #+#             */
/*   Updated: 2024/08/25 15:41:38 by mafferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	get_paths_len(char **paths)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 1;
	while (paths[i])
		i++;
	if (i > 1)
	{
		len = 1;
		while (j < i - 1)
		{
			len += ft_strlen(paths[j]) + 1;
			j++;
		}
	}
	return (len);
}

void	ptr_to_last(char **ptr, char **paths, int i)
{
	int	k;
	int	paths_len;

	**ptr = '/';
	(*ptr)++;
	k = 0;
	while (k < i - 1)
	{
		paths_len = ft_strlen(paths[k]);
		ft_memcpy(*ptr, paths[k], paths_len);
		*ptr += paths_len;
		if (k < i - 2)
			*(*ptr)++ = '/';
		k++;
	}
	**ptr = '\0';
}

char	*create_last(char **paths)
{
	int		len;
	char	*last;

	len = get_paths_len(paths);
	last = (char *)malloc(sizeof(char) * (len + 1));
	if (!last)
	{
		free_paths_cd(paths);
		return (NULL);
	}
	return (last);
}

char	**copy_env(char **env_copy, int new_size)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = (char **)malloc((new_size + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env_copy[i] && i < new_size)
	{
		new_env[i] = ft_strdup(env_copy[i]);
		if (!new_env[i])
		{
			i--;
			while (i >= 0)
			{
				free(new_env[i]);
				i--;
			}
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[new_size] = NULL;
	return (new_env);
}

char	*get_env_var(char **env_copy, char *var)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	j = 0;
	while (var[len])
		len++;
	while (env_copy[i])
	{
		j = 0;
		while (env_copy[i][j] == var[j] && var[j] != '\0'
			&& env_copy[i][j] != '=')
			j++;
		if (var[j] == '\0' && env_copy[i][j] == '=')
		{
			return (&env_copy[i][j + 1]);
		}
		i++;
	}
	return (NULL);
}
