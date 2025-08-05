/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:27:03 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 18:10:54 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	op_add(t_temp *temp1, t_tree *node, t_token **temp)
{
	temp1->red_node = create_token((*temp)->value, (*temp)->type,
			(*temp)->subtype, 0);
	temp1->red_node->old_expd = (*temp)->old_expd;
	if ((*temp)->next == NULL)
	{
		temp1->red_node->ambiguous = 1;
		insert_at_end(&node->red->red_op, temp1->red_node);
		char *s = "\0";
		temp1->red_node = create_token(s, (*temp)->type,
			(*temp)->subtype, 0);
		temp1->red_node->old_expd = (*temp)->old_expd;
		insert_at_end(&node->red->red_file, temp1->red_node);
		*temp = (*temp)->next;
		return ;
	}
	temp1->red_node->ambiguous = 0;
	insert_at_end(&node->red->red_op, temp1->red_node);
	*temp = (*temp)->next;
	temp1->red_node = create_token((*temp)->value, (*temp)->type,
			(*temp)->subtype, 0);
	temp1->red_node->old_expd = (*temp)->old_expd;
	insert_at_end(&node->red->red_file, temp1->red_node);
	*temp = (*temp)->next;
}

void	cmd_add(int *flag, t_token **temp, t_tree *node, t_temp *temp1)
{
	if (*flag == 0)
	{
		temp1->name_node = create_token((*temp)->value, (*temp)->type,
				(*temp)->subtype, 0);
		node->cmd->name = temp1->name_node;
		free((*temp)->old_expd);
		*flag = 1;
		*temp = (*temp)->next;
	}
	while (*temp && (*temp)->type != OP)
	{
		temp1->args_node = create_token((*temp)->value, (*temp)->type,
				(*temp)->subtype, 0);
		temp1->args_node->old_expd = (*temp)->old_expd;
		insert_at_end(&node->cmd->args, temp1->args_node);
		*temp = (*temp)->next;
	}
}

void	cmd_arg_2(t_token **temp, t_tree *node, t_temp *temp1)
{
	while (*temp && (*temp)->type != OP)
	{
		temp1->args_node = create_token((*temp)->value, (*temp)->type,
				(*temp)->subtype, 0);
		temp1->args_node->old_expd = (*temp)->old_expd;
		insert_at_end(&node->cmd->args, temp1->args_node);
		*temp = (*temp)->next;
	}
}

t_tree	*init(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	node->cmd = NULL;
	node->red = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->red = malloc(sizeof(t_red));
	node->cmd = malloc(sizeof(t_cmd));
	return (node);
}

void	node_add(t_token **temp, t_tree *node, t_temp *temp1, int *flag)
{
	if ((*temp)->expand == 1)
	{
		free((*temp)->old_expd);
		(*temp) = (*temp)->next;
		return ;
	}
	if ((*temp)->type == OP)
		op_add(temp1, node, temp);
	else
		cmd_add(flag, temp, node, temp1);
}
