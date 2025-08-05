/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_pipex_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafferre <mafferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:14 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/15 19:25:24 by mafferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

void	if_has_removed_var_nulls(int has_removed_var, char **result)
{
	int	final_length;

	if (has_removed_var)
	{
		final_length = ft_strlen(*result);
		if (final_length >= 2 && (((*result)[0] == '"' && (*result)[final_length
				- 1] == '"') || ((*result)[0] == '\''
					&& (*result)[final_length - 1] == '\'')))
		{
			if (final_length == 2)
				(*result)[0] = '\0';
			else
			{
				(*result)[final_length - 1] = '\0';
				ft_memmove(*result, *result + 1, final_length - 2);
			}
		}
	}
}

t_token	*lexing(char *line, char **env, t_minishell *mini)
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
	op_spaces = r_nexist_var(op_spaces, env);
	temp = ft_split_m(op_spaces, ' ');
	free(op_spaces);
	i[1] = ft_strstrlen(temp);
	split = remove_quotes(temp, env, mini);
	tokener(i, split->new, &token, temp);
	free_s_d(split->new, i);
	free(split);
	free_s(temp);
	return (token);
}

void	pipex_main(t_tree *tree, t_minishell *mini)
{
	int	is_builtin_cmd;
	int	i;

	if (!tree)
		return ;
	init_pipes(mini, mini->num_pipes);
	i = 0;
	is_builtin_cmd = 0;
	while (i <= mini->num_pipes)
	{
		if (check_here(mini, mini->current_node) == -1)
			return ;
		init_pipex_main(mini, mini->current_node, &is_builtin_cmd);
		g_sig_num = 0;
		if (mini->current_node->cmd->name != NULL && is_builtin_cmd)
			built(mini, mini->pids, &i, mini->pipes);
		else
			n_built(mini, i, mini->pipes, mini->pids);
		signal(SIGINT, SIG_IGN);
		close_p(i, mini->pipes, mini);
		mini->current_node = mini->current_node->next;
		i++;
	}
	wait_p(mini->pids, mini->num_pipes, mini);
	free_pipes_pids(mini);
}
