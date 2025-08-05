/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:28 by erferrei          #+#    #+#             */
/*   Updated: 2024/09/26 20:00:41 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*extract_var_name(const char *str)
{
	int	len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
	{
		if (is_digit(str[len]))
		{
			len = 1;
			break ;
		}
		len++;
	}
	return (ft_strsub(str, 0, len));
}

void	insert_at_end_tree(t_tree **head, t_tree *new_token)
{
	t_tree	*tmp;

	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->prev = tmp;
	new_token->next = NULL;
}

void	init_parser(t_tree *node, int *flag)
{
	*flag = 0;
	node->red->red_op = NULL;
	node->red->red_file = NULL;
	node->cmd->args = NULL;
	node->cmd->name = NULL;
}

t_tree	*parse(t_token *token)
{
	t_tree	*tree;
	t_tree	*node;
	t_token	*temp;
	t_temp	temp1;
	int		flag;

	temp1.args_node = NULL;
	temp = token;
	flag = 0;
	tree = NULL;
	while (temp)
	{
		node = init();
		init_parser(node, &flag);
		while (temp && temp->subtype != PIPE)
			node_add(&temp, node, &temp1, &flag);
		insert_at_end_tree(&tree, node);
		if (temp)
			temp = temp->next;
	}
	free(temp);
	return (tree);
}
