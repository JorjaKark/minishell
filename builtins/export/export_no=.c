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

void	var_does_not_exist_case_no_equal(char *var_name, char ***env_copy)
{
	int	len;

	len = env_count(*env_copy) + 1;
	ft_expand(env_copy, len, var_name);
}

void	no_equal_var(char *argv, char ***env_copy)
{
	char	*var_value;

	var_value = NULL;
	put_null_var_value(&var_value);
	if (does_var_exist_export(argv, *env_copy))
	{
		free(var_value);
		return ;
	}
	else
		var_does_not_exist_case_no_equal(argv, env_copy);
	free(var_value);
}
