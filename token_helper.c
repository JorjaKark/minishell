/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:27:07 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/01 19:44:24 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

void	put_token(t_token **head, char *value, int expand, char *t)
{
	t_token	*token;

	if (value == NULL)
	{
		token = create_token("", EXP, -1, expand);
		token->old_expd = ft_strdup(t);
		insert_at_end(head, token);
		return ;
	}
	if (ft_strncmp(value, "|", 1) == 0 && ft_strncmp(t, "|", 1) == 0)
		token = create_token(value, OP, PIPE, 0);
	else if (ft_strncmp(value, ">>", 2) == 0 && ft_strncmp(t, ">>", 2) == 0)
		token = create_token(value, OP, RGREAT, 0);
	else if (ft_strncmp(value, ">", 1) == 0 && ft_strncmp(t, ">", 1) == 0)
		token = create_token(value, OP, GREAT, 0);
	else if (ft_strncmp(value, "<<", 2) == 0 && ft_strncmp(t, "<<", 2) == 0)
		token = create_token(value, OP, RLESS, 0);
	else if (ft_strncmp(value, "<", 1) == 0 && ft_strncmp(t, "<", 1) == 0)
		token = create_token(value, OP, LESS, 0);
	else
		token = create_token(value, EXP, -1, 0);
	token->old_expd = NULL;
	if (expand)
		token->old_expd = ft_strdup(t);
	insert_at_end(head, token);
}

int	is_between_quotes(char *line, int i)
{
	int	quote;

	quote = 0;
	while (i >= 0)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		i--;
	}
	return (quote);
}

void	add_s(char *line, char *new_line, int *i, int *j)
{
	if (line[*i + 1] == line[*i] && (line[*i] == '>' || line[*i] == '<'))
	{
		new_line[*j] = ' ';
		*j = *j + 1;
		new_line[*j] = line[*i];
		*j = *j + 1;
		*i = *i + 1;
		new_line[*j] = line[*i];
		*j = *j + 1;
		new_line[*j] = ' ';
	}
	else
	{
		if (*j == 0 || new_line[*j - 1] != ' ')
		{
			new_line[*j] = ' ';
			*j = *j + 1;
		}
		new_line[*j] = line[*i];
		*j = *j + 1;
		new_line[*j] = ' ';
	}
}

char	*add_space_op(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = (char *)malloc(sizeof(char) * ft_strlen(line) * 2 + 2);
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (!is_between_quotes(line, i) && (line[i] == '|' || line[i] == '<'
				|| line[i] == '>'))
		{
			add_s(line, new_line, &i, &j);
		}
		else
			new_line[j] = line[i];
		i++;
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}
