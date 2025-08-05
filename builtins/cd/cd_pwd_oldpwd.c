/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafferre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:42:07 by mafferre          #+#    #+#             */
/*   Updated: 2024/08/25 15:42:09 by mafferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*var_plus_value(char *var, char *value)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char *)malloc(ft_strlen(var) + ft_strlen(value) + 2);
	if (!result)
		return (NULL);
	while (var[i])
	{
		result[i] = var[i];
		i++;
	}
	result[i++] = '=';
	while (value[j])
		result[i++] = value[j++];
	result[i] = '\0';
	return (result);
}

int	add_env_var(char ***env_copy, char *new_var)
{
	int		i;
	int		env_len;
	char	**new_env;

	i = 0;
	env_len = env_count(*env_copy);
	new_env = (char **)malloc((env_len + 2) * sizeof(char *));
	if (!new_env)
	{
		free(new_var);
		return (-1);
	}
	while ((*env_copy)[i])
	{
		new_env[i] = (*env_copy)[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free_env(*env_copy);
	*env_copy = new_env;
	return (0);
}

int	replace_env_var(char **env_copy, char *var, char *new_var)
{
	int	i;
	int	j;

	i = 0;
	while (env_copy[i])
	{
		j = 0;
		while (env_copy[i][j] == var[j] && var[j] != '\0'
			&& env_copy[i][j] != '=')
			j++;
		if (var[j] == '\0' && env_copy[i][j] == '=')
		{
			free(env_copy[i]);
			env_copy[i] = new_var;
			return (0);
		}
		i++;
	}
	return (-1);
}

int	update_env_var(char ***env_copy, char *var, char *value)
{
	char	*new_var;

	new_var = var_plus_value(var, value);
	if (!new_var)
		return (-1);
	if (replace_env_var(*env_copy, var, new_var) == 0)
		return (0);
	return (add_env_var(env_copy, new_var));
}

void	update_pwd(char ***env_copy)
{
	char	cwd[4096];
	char	*old_pwd;

	old_pwd = get_env_var(*env_copy, "PWD");
	if (old_pwd)
	{
		if (update_env_var(env_copy, "OLDPWD", old_pwd) != 0)
			return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (update_env_var(env_copy, "PWD", cwd) != 0)
			return ;
	}
}
