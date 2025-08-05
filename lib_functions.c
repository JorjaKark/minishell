/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafferre <mafferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:17 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/15 19:27:12 by mafferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_fcalloc(char **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		str[i] = (char *)malloc(sizeof(char) * 1);
		if (!str[i])
		{
			while (i >= 0)
				free(str[i--]);
			free(str);
			return ;
		}
		str[i][0] = '\0';
		i++;
	}
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			i++;
	}
	return (i);
}

char	*ft_strjoin_char(char *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL)
	{
		str = (char *)malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = c;
		str[1] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	return (str);
}
