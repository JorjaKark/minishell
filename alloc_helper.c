/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:12 by erferrei          #+#    #+#             */
/*   Updated: 2024/09/10 20:25:15 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	count_helper(char const *s, int c, int *a, int *count)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i])
	{
		if (s[i] == c || (s[i] >= 9 && s[i] <= 13))
			*a = 0;
		else if ((s[i] != c && !(s[i] >= 9 && s[i] <= 13)) && *a == 0)
		{
			*count = *count + 1;
			*a = 1;
		}
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (!s[i])
				break ;
		}
		i++;
	}
}

int	count_words(char const *s, char c)
{
	int	count;
	int	a;

	count = 0;
	a = 0;
	count_helper(s, c, &a, &count);
	return (count);
}

void	check_alloc(int *i, int *value)
{
	if (i[1] - 1 == i[3])
		*value = *value + 1;
}

void	is_white(int **i, char const *s, int *a)
{
	if ((s[(*i)[0]] != (*i)[2] || (s[(*i)[0]] >= 9 && s[(*i)[0]] <= 13))
		&& *a == 0)
	{
		(*i)[1] = (*i)[1] + 1;
		*a = 1;
	}
}

void	alloc_helper(int *i, int a, int *value, char const *s)
{
	while (s[i[0]])
	{
		if (s[i[0]] == i[2] || (s[i[0]] >= 9 && s[i[0]] <= 13))
			a = 0;
		else
			is_white(&i, s, &a);
		if (s[i[0]] == '\'' || s[i[0]] == '\"')
		{
			i[0]++;
			if (i[1] - 1 == i[3])
				*value = *value + 1;
			while (s[i[0]] && s[i[0]] != s[i[0] - 1])
			{
				i[0]++;
				check_alloc(i, value);
			}
			if (!s[i[0]])
				break ;
			check_alloc(i, value);
		}
		else if ((i[1] - 1) == i[3] && a == 1)
			*value = *value + 1;
		i[0]++;
	}
}
