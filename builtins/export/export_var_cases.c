/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:36:36 by mafferre          #+#    #+#             */
/*   Updated: 2024/09/11 09:21:27 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	var_exists_case_helper(char *var_name, char *var_value,
		char **new_var_total)
{
	char	*temp;

	*new_var_total = ft_strjoin(var_name, "=");
	if (*new_var_total)
	{
		temp = ft_strjoin(*new_var_total, var_value);
		free(*new_var_total);
		*new_var_total = temp;
	}
}

void	var_exists_case(char *var_name, char *var_value, char ***env_copy)
{
	int		i;
	char	*new_var_total;

	i = 0;
	new_var_total = NULL;
	while ((*env_copy)[i])
	{
		if (ft_strncmp((*env_copy)[i], var_name, ft_strlen(var_name)) == 0
			&& ((*env_copy)[i][ft_strlen(var_name)] == '='
				|| (*env_copy)[i][ft_strlen(var_name)] == '\0'))
		{
			var_exists_case_helper(var_name, var_value, &new_var_total);
			if (new_var_total)
			{
				free((*env_copy)[i]);
				(*env_copy)[i] = new_var_total;
			}
			return ;
		}
		i++;
	}
}

void	var_does_not_exist_case(char *var_name, char *var_value,
		char ***env_copy)
{
	char	*new_var_equal;
	char	*new_var_total;
	int		len;

	new_var_equal = ft_strjoin(var_name, "=");
	if (!new_var_equal)
		return ;
	new_var_total = ft_strjoin(new_var_equal, var_value);
	free(new_var_equal);
	if (!new_var_total)
		return ;
	len = env_count(*env_copy) + 1;
	ft_expand(env_copy, len, new_var_total);
	free(new_var_total);
}
