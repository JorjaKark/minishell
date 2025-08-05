/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:22 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 18:58:17 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

void	find_sh_variable(char **env)
{
	int		i;
	char	*temp;
	char	*temp1;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			temp = get_env_value("SHLVL", env);
			temp1 = ft_itoa(ft_atoi(temp) + 1);
			free(temp);
			temp = ft_strjoin("SHLVL=", temp1);
			free(temp1);
			free(env[i]);
			env[i] = ft_strdup(temp);
			free(temp);
			break ;
		}
		i++;
	}
}

void	init_var_main(t_minishell *mini, char **env, int ac, char **av)
{
	(void)ac;
	(void)av;
	mini->tree = NULL;
	mini->node = init();
	insert_at_end_tree(&mini->tree, mini->node);
	mini->env_copy = ft_strdupdup(env);
	find_sh_variable(mini->env_copy);
	mini->cmd_arg = NULL;
	mini->m_g_sig_num = 0;
	g_sig_num = 0;
	mini->flag_pipes = 0;
}


char	**fake_remove_loop(t_counter *cnt, char **split,
			char **env, t_minishell *mini)
{
	(void)env;
	while (split[cnt->c][cnt->j])
	{
		if (is_quote(split[cnt->c][cnt->j]))
			remove_q(split, cnt, &cnt->flag, mini);
		else
		{
			cnt->new[cnt->i] = ft_strjoin_char(cnt->new[cnt->i],
					split[cnt->c][cnt->j]);
			cnt->j++;
		}
	}
	return (cnt->new);
}

t_counter	*fake_remove_quotes(char **split, char **env, t_minishell *mini)
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
		fake_remove_loop(cnt, split, env, mini);
		cnt->i++;
		cnt->c++;
	}
	cnt->new[cnt->i] = NULL;
	return (cnt);
}

t_token	*fake_lexing(char *line, char **env, t_minishell *mini)
{
	t_counter	*split;
	char		**temp;
	char		*op_spaces;
	int			i[2];
	t_token		*token;

	split = NULL;
	i[0] = 0;
	token = NULL;
	op_spaces = NULL;
	op_spaces = add_space_op(line);
	//op_spaces = r_nexist_var(op_spaces, env);
	temp = ft_split_m(op_spaces, ' ');
	free(op_spaces);
	i[1] = ft_strstrlen(temp);
	split = fake_remove_quotes(temp, env, mini);
	tokener(i, split->new, &token, temp);
	free_s_d(split->new, i);
	free(split);
	free_s(temp);
	return (token);
}

int	fake_check_op_pipe(t_token *tmp)
{
	if (tmp->type == OP)
	{
		if (tmp->next == NULL)
		{
			write(2, "ambiguous redirect\n", 20);
			return (1);
		}
	}
	if (tmp->subtype == PIPE)
	{
		if (tmp->next == NULL || tmp->next->subtype == PIPE
			|| tmp->prev == NULL)
		{
			write(STDERR_FILENO, "syntax error near ", 18);
			return (printf("unexpected token `%s'\n", tmp->next->value), 1);
		}
	}
	return (0);
}

int	fake_check_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (fake_check_op_pipe(tmp))
			return (1);
		if (check_greats(tmp))
			return (1);
		if (check_less(tmp))
			return (1);
		tmp = tmp->next;
	}
	
	return (0);
}

void	fake_free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->old_expd)
			free(tmp->old_expd);
		free(tmp->value);
		free(tmp);
	}
}

void	lex_parse_exec(t_minishell *mini)
{
	mini->token = fake_lexing(mini->line, mini->env_copy, mini);
	if (mini->token && check_syntax(mini->token))
	{
		//free_tokens(mini->token);
		mini->m_g_sig_num = 2 - 128;
	}
	else
	{	
		fake_free_tokens(mini->token);
		mini->token = lexing(mini->line, mini->env_copy, mini);
		if (mini->token && fake_check_syntax(mini->token))
		{
			mini->m_g_sig_num = 1 - 128;	
			return ;
		}
		parse_exec(mini);
		free_error2(mini);
	}
}

void	free_if_b(t_minishell *mini)
{
	free(mini->line);
	free_tokens(mini->token);
}
