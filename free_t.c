/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:55 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/08 19:29:29 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
		if (token && token->old_expd)
			free(token->old_expd);
	}
}

void	free_red(t_red *red)
{
	if (red)
	{
		if (red->red_op && red->red_op->old_expd)
			free(red->red_op->old_expd);
		if (red->red_file && red->red_file->old_expd)
			free(red->red_file->old_expd);
		free_token(red->red_op);
		free_token(red->red_file);
		free(red);
		red = NULL;
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->name)
		{
			free_token(cmd->name);
		}
		free(cmd->args);
		free(cmd);
		cmd = NULL;
	}
}

void	init_tree(t_tree **tree)
{
	*tree = (t_tree *)malloc(sizeof(t_tree));
	if (*tree == NULL)
		return ;
	(*tree)->cmd = NULL;
	(*tree)->red = NULL;
	(*tree)->next = NULL;
	(*tree)->prev = NULL;
}

void	free_tree(t_tree *tree)
{
	t_tree	*temp;

	while (tree)
	{
		temp = tree;
		tree = tree->next;
		if (temp->cmd)
			free_cmd(temp->cmd);
		if (temp->red)
			free_red(temp->red);
		free(temp);
	}
}
