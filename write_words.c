/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:27:19 by erferrei          #+#    #+#             */
/*   Updated: 2024/09/10 20:27:20 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_helper(char const *s, t_vars *var, char **strstr, int index)
{
	if (s[var->i] == '\'' || s[var->i] == '\"')
	{
		var->quote = s[var->i];
		if (var->count - 1 == index)
			strstr[index][var->m++] = s[var->i];
		var->i++;
		while (s[var->i] && s[var->i] != var->quote)
		{
			if (var->count - 1 == index)
				strstr[index][var->m++] = s[var->i];
			var->i++;
		}
		if (!s[var->i])
			return (2);
		else if (var->count - 1 == index)
			strstr[index][var->m++] = s[var->i];
		return (1);
	}
	return (0);
}

void	write_words(char **strstr, char const *s, char c, int index)
{
	t_vars	var;
	int		if_is;

	var.i = 0;
	var.a = 0;
	var.count = 0;
	var.m = 0;
	while (s[var.i])
	{
		if (s[var.i] == c || (s[var.i] >= 9 && s[var.i] <= 13))
			var.a = 0;
		else if ((s[var.i] != c || (s[var.i] >= 9 && s[var.i] <= 13))
			&& var.a == 0)
		{
			var.count++;
			var.a = 1;
		}
		if_is = write_helper(s, &var, strstr, index);
		if (if_is == 2)
			break ;
		else if (if_is == 0 && (var.count - 1) == index && var.a == 1)
			strstr[index][var.m++] = s[var.i];
		var.i++;
	}
	strstr[index][var.m] = '\0';
}
