/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:40 by erferrei          #+#    #+#             */
/*   Updated: 2024/09/10 20:26:41 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	size_list(t_token *node)
{
	int	size;

	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}

void	dup_value_curr_arg(t_token *current_arg, char ***argv, int *i)
{
	while (current_arg)
	{
		(*argv)[*i] = ft_strdup(current_arg->value);
		free(current_arg->value);
		current_arg->value = NULL;
		current_arg = current_arg->next;
		*i = *i + 1;
	}
}

char	**t_cmd_to_argv(t_tree *node)
{
	t_tree	*temp;
	int		size;
	int		i;
	char	**argv;
	t_token	*current_arg;

	temp = node;
	size = size_list(temp->cmd->args);
	argv = malloc(sizeof(char *) * (2 + size));
	if (!argv)
		return (NULL);
	i = 1;
	if (temp->cmd->name == NULL)
		argv[0] = NULL;
	else
		argv[0] = ft_strdup(temp->cmd->name->value);
	current_arg = temp->cmd->args;
	dup_value_curr_arg(current_arg, &argv, &i);
	temp = node;
	argv[i] = NULL;
	return (argv);
}
