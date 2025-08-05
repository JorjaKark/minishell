/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafferre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:47:44 by mafferre          #+#    #+#             */
/*   Updated: 2024/08/25 19:47:46 by mafferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_split(char **split_arr)
{
	int	i;

	i = 0;
	if (split_arr)
	{
		while (split_arr[i])
			free(split_arr[i++]);
		free(split_arr);
	}
}

void	free_export(char *new_var_equal, char *new_var_total, int i,
		char ***env_copy)
{
	free(new_var_equal);
	free((*env_copy)[i]);
	(*env_copy)[i] = ft_strdup(new_var_total);
	free(new_var_total);
}

void	free_s_new(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	put_null_var_value(char **var_value)
{
	if (*var_value)
		free(*var_value);
	*var_value = malloc(1);
	if (*var_value == NULL)
		return ;
	(*var_value)[0] = '\0';
}

void	put_valid_value(char **var_value, char **var_arr)
{
	if (*var_value)
		free(*var_value);
	*var_value = ft_strdup(var_arr[1]);
	if (*var_value == NULL)
		return ;
	make_it_valid(var_value);
}
