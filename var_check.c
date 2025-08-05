/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:27:16 by erferrei          #+#    #+#             */
/*   Updated: 2024/09/11 09:21:16 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	does_var_exist(const char *var_name, char **env)
{
	int	var_len;
	int	i;

	i = 0;
	var_len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, var_len) == 0
			&& env[i][var_len] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	env_count(char **env)
{
	int	count;

	count = 0;
	while (env[count] != NULL)
	{
		count++;
	}
	return (count);
}

void	get_and_free(char **new_env, int i, char **var, char **value)
{
	var = ft_split(new_env[i - 1], '=');
	*value = var[1];
	free(var[0]);
	free(var);
}

char	*get_env_value(const char *var_name, char **env)
{
	int		env_size;
	int		i;
	char	**new_env;
	char	**var;
	char	*value;

	var = NULL;
	value = NULL;
	i = 0;
	new_env = env;
	env_size = env_count(env);
	if (does_var_exist(var_name, env))
	{
		while (i < env_size)
		{
			if (ft_strncmp(env[i++], var_name, ft_strlen(var_name)) == 0)
			{
				get_and_free(new_env, i, var, &value);
				break ;
			}
		}
	}
	return (value);
}
