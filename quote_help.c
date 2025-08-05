/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:43 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/08 19:31:36 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_strdupdup(char **s)
{
	int		i;
	char	**new;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (ft_strstrlen(s) + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = ft_strdup(s[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ign(char *new, t_counter *cnt)
{
	free(new);
	new = NULL;
	cnt->i--;
}

void	advance(char **split, t_counter *cnt)
{
	while (split[cnt->c][cnt->j])
		cnt->j++;
}

void	advance_quote(char **split, t_counter *cnt, char quote)
{
	if (split[cnt->c][cnt->j] == quote)
		cnt->j++;
}

void	remove_q(char **split, t_counter *cnt, int *flag, t_minishell *mini)
{
	char	quote;

	quote = split[cnt->c][cnt->j++];
	while (split[cnt->c][cnt->j] && split[cnt->c][cnt->j] != quote)
	{
		if (quote == '\'')
			cnt->new[cnt->i] = ft_strjoin_char(cnt->new[cnt->i],
					split[cnt->c][cnt->j]);
		else
		{
			if (cnt->new[cnt->i] != NULL)
				free(cnt->new[cnt->i]);
			cnt->new[cnt->i] = expand_var(split[cnt->c],
					mini->env_copy, flag, mini);
			if (*flag == 1)
			{
				ign(cnt->new[cnt->i], cnt);
				break ;
			}
			advance(split, cnt);
			cnt->j--;
		}
		cnt->j++;
	}
	advance_quote(split, cnt, quote);
}
