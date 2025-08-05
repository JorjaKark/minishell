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

void	var_exists_case_concatenation_helper1(char *var_name, char *var_value,
		char ***env_copy, int i)
{
	char	*line;

	if (!ft_strncmp((*env_copy)[i], var_name, ft_strlen(var_name))
		&& ((*env_copy)[i][ft_strlen(var_name)] != '\0'
			&& (*env_copy)[i][ft_strlen(var_name)] == '='))
	{
		line = ft_strjoin((*env_copy)[i], var_value);
		if (line)
		{
			free((*env_copy)[i]);
			(*env_copy)[i] = line;
		}
	}
}

void	var_exists_case_concatenation_helper2(char *var_name, char *var_value,
		char ***env_copy, int i)
{
	char	*line;
	char	*temp_line;

	if (!ft_strncmp((*env_copy)[i], var_name, ft_strlen(var_name))
		&& ((*env_copy)[i][ft_strlen(var_name)] == '\0'))
	{
		temp_line = ft_strjoin((*env_copy)[i], "=");
		if (temp_line)
		{
			line = ft_strjoin(temp_line, var_value);
			free(temp_line);
			if (line)
			{
				free((*env_copy)[i]);
				(*env_copy)[i] = line;
			}
		}
	}
}

void	var_exists_case_concatenation(char *var_name, char *var_value,
		char ***env_copy)
{
	int	i;

	i = 0;
	while ((*env_copy)[i])
	{
		var_exists_case_concatenation_helper1(var_name, var_value, env_copy, i);
		var_exists_case_concatenation_helper2(var_name, var_value, env_copy, i);
		if (!ft_strncmp((*env_copy)[i], var_name, ft_strlen(var_name)))
			break ;
		i++;
	}
}

void	concatenation_helper(char **var_arr, char **var_name, char **var_value)
{
	*var_name = ft_strdup(var_arr[0]);
	if (!*var_name)
	{
		free_split(var_arr);
		return ;
	}
	if (var_arr[1])
	{
		put_valid_value(var_value, var_arr);
	}
	else
	{
		put_null_var_value(var_value);
	}
}

void	concatenation(char *argv, char ***env_copy)
{
	char	**var_arr;
	char	*var_name;
	char	*var_value;

	var_value = NULL;
	var_arr = ft_split(argv, '+');
	if (!var_arr)
		return ;
	concatenation_helper(var_arr, &var_name, &var_value);
	if (does_var_exist_export(var_name, *env_copy))
	{
		var_exists_case_concatenation(var_name, var_value, env_copy);
	}
	else
	{
		var_does_not_exist_case(var_name, var_value, env_copy);
	}
	free(var_value);
	free(var_name);
	free_split(var_arr);
}
