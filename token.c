/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:27:11 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 18:10:19 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	q_check(int *a, int *i, char *line, char quote)
{
	*a = 1;
	*i = *i + 1;
	while (line[*i] && line[*i] != quote)
		*i = *i + 1;
	if (!line[*i])
		return (1);
	*a = 0;
	return (0);
}

int	check_quote(char *line)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			if (q_check(&a, &i, line, '\''))
				return (a);
		}
		else if (line[i] == '\"')
		{
			if (q_check(&a, &i, line, '\"'))
				return (a);
		}
		i++;
	}
	return (a);
}

t_token	*dup_token(t_token *token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(token->value);
	new_token->type = token->type;
	new_token->subtype = token->subtype;
	new_token->precedence = token->precedence;
	new_token->null = token->null;
	new_token->expand = token->expand;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	insert_at_end(t_token **head, t_token *new_token)
{
	t_token	*tmp;

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
}

t_token	*create_token(char *value, int type, int subtype, int expand)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->subtype = subtype;
	if (value == NULL)
		token->null = 1;
	else
		token->null = 0;
	if (subtype == PIPE)
		token->precedence = 1;
	else if (subtype == GREAT || subtype == RGREAT)
		token->precedence = 2;
	else if (subtype == LESS || subtype == RLESS)
		token->precedence = 3;
	else
		token->precedence = 0;
	token->expand = expand;
	token->ambiguous = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
