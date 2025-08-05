/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:59 by erferrei          #+#    #+#             */
/*   Updated: 2024/09/11 09:20:42 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include <stdio.h>

int	check_quote_alloc(int *i, int *count, int *value, char const *s)
{
	char	quote;

	if (s[*i] == '\'' || s[*i] == '\"')
	{
		quote = s[*i];
		*i = *i + 1;
		if (count[0] - 1 == count[1])
			*value = *value + 1;
		while (s[*i] && s[*i] != quote)
		{
			*i = *i + 1;
			if (count[0] - 1 == count[1])
				*value = *value + 1;
		}
		if (!s[*i])
			return (1);
		else if (count[0] - 1 == count[1])
			*value = *value + 1;
	}
	return (0);
}

int	alloc_words(char const *s, char c, int index)
{
	int	i;
	int	value;
	int	count[3];

	i = 0;
	count[0] = 0;
	count[1] = index;
	count[2] = 0;
	value = 1;
	while (s[i])
	{
		if (s[i] == c || (s[i] >= 9 && s[i] <= 13))
			count[2] = 0;
		else if ((s[i] != c || (s[i] >= 9 && s[i] <= 13)) && count[2] == 0)
		{
			count[0]++;
			count[2] = 1;
		}
		if (check_quote_alloc(&i, count, &value, s) == 1)
			break ;
		else if ((count[0] - 1) == index && count[2] == 1)
			value++;
		i++;
	}
	return (value);
}

void	free_s(char **s)
{
	int	i;

	i = 0;
	if (!s)
	{
		free(s);
		return ;
	}
	while (s[i])
		free(s[i++]);
	free(s);
	s = NULL;
}

char	**ft_split_m(char const *s, char c)
{
	int		index;
	char	**strstr;
	int		word_count;

	word_count = count_words(s, c);
	strstr = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!strstr)
		return (NULL);
	index = 0;
	while (word_count > 0)
	{
		strstr[index] = (char *)malloc(alloc_words(s, c, index) * sizeof(char));
		if (!strstr[index])
		{
			free_s(strstr);
			return (NULL);
		}
		write_words(strstr, s, c, index);
		word_count--;
		index++;
	}
	strstr[index] = 0;
	return (strstr);
}
