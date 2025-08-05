/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_not_exist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafferre <mafferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:04:32 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/15 19:24:50 by mafferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	v_exist(const char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	re_loop(char **str, char **env, int (*i)[2], char **result)
{
	char	*name;
	int		start;
	int		end;

	start = (*i)[0] + 1;
	end = start;
	if (!ft_isalnum((*str)[start]) && (*str)[start] != '_')
	{
		(*result)[(*i)[1]++] = (*str)[(*i)[0]++];
		(*result)[(*i)[1]++] = (*str)[(*i)[0]++];
	}
	else
	{
		while ((*str)[end] && (ft_isalnum((*str)[end])
				|| (*str)[end] == '_'))
			end++;
		name = ft_strndup(&(*str)[start], end - start);
		if (v_exist(name, env))
			while ((*i)[0] < end)
				(*result)[(*i)[1]++] = (*str)[(*i)[0]++];
		free(name);
		(*i)[0] = end;
	}
}

char	*r_nexist_var(char *str, char **env)
{
	char	*result;
	int		i[2];
	int		str_len;

	str_len = ft_strlen(str);
	result = malloc(str_len + 1);
	if (!result)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		if (str[i[0]] == '$')
			re_loop(&str, env, &i, &result);
		else
			result[i[1]++] = str[i[0]++];
		if (str[i[0] - 1] == '\0')
			break ;
	}
	if (i[1] == 0 || result[i[1] - 1] != '\0')
		result[i[1]] = '\0';
	free(str);
	return (result);
}
