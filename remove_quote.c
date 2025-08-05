/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:51 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/08 19:26:46 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**remove_loop(t_counter *cnt, char **split,
			char **env, t_minishell *mini)
{
	while (split[cnt->c][cnt->j])
	{
		if (is_quote(split[cnt->c][cnt->j]))
			remove_q(split, cnt, &cnt->flag, mini);
		else if (split[cnt->c][cnt->j] == '$')
		{
			free(cnt->new[cnt->i]);
			cnt->new[cnt->i] = expand_var(split[cnt->c], env, &cnt->flag, mini);
			if (cnt->flag == 1)
			{
				free(cnt->new[cnt->i]);
				cnt->new[cnt->i--] = NULL;
				break ;
			}
			while (split[cnt->c][cnt->j])
				cnt->j++;
		}
		else
		{
			cnt->new[cnt->i] = ft_strjoin_char(cnt->new[cnt->i],
					split[cnt->c][cnt->j]);
			cnt->j++;
		}
	}
	return (cnt->new);
}

t_counter	*remove_quotes(char **split, char **env, t_minishell *mini)
{
	t_counter	*cnt;

	cnt = (t_counter *)malloc(sizeof(t_counter));
	if (!cnt)
		return (NULL);
	cnt->c = 0;
	cnt->i = 0;
	cnt->j = 0;
	cnt->new = (char **)malloc(sizeof(char *) * (ft_strstrlen(split) + 1));
	if (!cnt->new)
		return (NULL);
	while (split[cnt->c])
	{
		cnt->j = 0;
		cnt->flag = 0;
		cnt->new[cnt->i] = NULL;
		remove_loop(cnt, split, env, mini);
		cnt->i++;
		cnt->c++;
	}
	cnt->new[cnt->i] = NULL;
	return (cnt);
}

void	tokener(int *i, char **split, t_token **token, char **t)
{
	int	expand;
	int	j;

	while (i[0] < i[1])
	{
		expand = 0;
		j = 0;
		while (t[i[0]][j])
		{
			if (!t[i[0]][j + 1])
				break ;
			if (t[i[0]][j] == '$' && (ft_isalnum(t[i[0]][j + 1])
					|| t[i[0]][j + 1] == '_'))
			{
				expand = 1;
				break ;
			}
			j++;
		}
		put_token(token, split[i[0]], expand, t[i[0]]);
		i[0] = i[0] + 1;
	}
}

void	free_s_d(char **split, int *i)
{
	int	j;

	j = 0;
	while (i[1] > 0)
	{
		free(split[j]);
		j++;
		i[1]--;
	}
	free(split);
}
