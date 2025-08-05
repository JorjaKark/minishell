/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:04:00 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/12 17:11:18 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "pipex.h"


extern int	g_sig_num;

void	built_main(t_token *redirection, t_token *redirection_f,
		t_minishell *mini, t_tree *current_node)
{
	handle_red(redirection, redirection_f, mini, current_node);
	execute(mini->cmd_arg, mini->env_copy, mini);
	dup2(mini->saved_stdin, STDIN_FILENO);
	dup2(mini->saved_stdout, STDOUT_FILENO);
	close(mini->saved_stdin);
	close(mini->saved_stdout);
}

int	count_commands(t_tree *tree)
{
	int		count;
	t_tree	*current;

	count = 0;
	current = tree;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}
