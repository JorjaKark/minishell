/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:52 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 17:11:22 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

char	*remove_quotes_old(char *split)
{
	int		i;
	char	quote;
	char	*new;

	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(split) + 1));
	if (!new)
		return (NULL);
	ft_bzero(new, ft_strlen(split) + 1);
	while (split[i])
	{
		if (is_quote(split[i]))
		{
			quote = split[i++];
			while (split[i] && split[i] != quote)
				new = ft_strjoin_char(new, split[i++]);
			if (split[i] == quote)
				i++;
		}
		else
			new = ft_strjoin_char(new, split[i++]);
	}
	return (new);
}

void	expand_n(t_expand *exp, char **env, int *flag, const char *str)
{
	exp->new_str[exp->j] = '\0';
	exp->var_name = extract_var_name(&str[exp->i + 1]);
	exp->var_value = get_env_value(exp->var_name, env);
	if (exp->var_value)
	{
		while (exp->var_value[exp->k])
			exp->new_str[exp->j++] = exp->var_value[exp->k++];
	}
	else
		*flag = 1;
	exp->i += ft_strlen(exp->var_name) + 1;
	exp->k = 0;
	free(exp->var_name);
	free(exp->var_value);
}

void	expand_e(t_expand *exp, t_minishell *mini)
{
	exp->new_str[exp->j] = '\0';
	if (g_sig_num > 0)
		exp->var_value = ft_itoa(g_sig_num + 128);
	else
	{
		if (mini->m_g_sig_num == 0)
			exp->var_value = ft_itoa(0);
		else
			exp->var_value = ft_itoa(mini->m_g_sig_num + 128);
	}
	while (exp->var_value[exp->k])
		exp->new_str[exp->j++] = exp->var_value[exp->k++];
	exp->i += 2;
	exp->k = 0;
	free(exp->var_value);
}

void	init_exp(t_expand *exp)
{
	exp->i = 0;
	exp->j = 0;
	exp->k = 0;
}

char	*expand_var(const char *str, char **env, int *flag, t_minishell *mini)
{
	t_expand	*exp;
	char		*temp;

	exp = (t_expand *)malloc(sizeof(t_expand));
	init_exp(exp);
	exp->new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) * 4996 + 1));
	if (!exp->new_str)
		return (NULL);
	ft_memset(exp->new_str, 0, ft_strlen(str) * 2 + 1);
	while (str[exp->i])
	{
		if (str[exp->i] == '$' && str[exp->i + 1] == '?')
			expand_e(exp, mini);
		else if (str[exp->i] == '$' && (ft_isalnum(str[exp->i + 1])
				|| str[exp->i + 1] == '_'))
			expand_n(exp, env, flag, str);
		else
			exp->new_str[exp->j++] = str[exp->i++];
	}
	exp->new_str[exp->j] = '\0';
	temp = remove_quotes_old(exp->new_str);
	free(exp->new_str);
	free(exp);
	return (temp);
}
