/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafferre <mafferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:30 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/15 19:02:31 by mafferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_greats(t_token *tmp)
{
	if (tmp->subtype == GREAT)
	{
		if (tmp->next == NULL || tmp->next->subtype == PIPE
			|| tmp->next->subtype == LESS || tmp->next->subtype == RLESS
			|| tmp->next->subtype == RGREAT)
		{
			write(STDERR_FILENO, "syntax error near ", 18);
			return (printf("unexpected token `%s'\n", tmp->next->value), 1);
		}
	}
	if (tmp->subtype == RGREAT)
	{
		if (tmp->next == NULL || tmp->next->subtype == PIPE
			|| tmp->next->subtype == LESS || tmp->next->subtype == RLESS
			|| tmp->next->subtype == RGREAT || tmp->next->subtype == GREAT)
		{
			write(STDERR_FILENO, "syntax error near ", 18);
			return (printf("unexpected token `%s'\n", tmp->next->value), 1);
		}
	}
	return (0);
}

int	check_less(t_token *tmp)
{
	if (tmp->subtype == LESS)
	{
		if (tmp->next == NULL || tmp->next->subtype == PIPE
			|| tmp->next->subtype == GREAT || tmp->next->subtype == RLESS
			|| tmp->next->subtype == RGREAT)
		{
			write(STDERR_FILENO, "syntax error near ", 18);
			return (printf("unexpected token `%s'\n", tmp->next->value), 1);
		}
	}
	if (tmp->subtype == RLESS)
	{
		if (tmp->next == NULL || tmp->next->subtype == PIPE
			|| tmp->next->subtype == GREAT || tmp->next->subtype == RLESS
			|| tmp->next->subtype == RGREAT || tmp->next->subtype == LESS)
		{
			write(STDERR_FILENO, "syntax error near ", 18);
			return (printf("unexpected token `%s'\n", tmp->next->value), 1);
		}
	}
	return (0);
}

int	check_op_pipe(t_token *tmp)
{
	if (tmp->type == OP)
	{
		if (tmp->next == NULL)
		{
			printf("syntax error near unexpected token `newline'\n");
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

int	check_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (check_op_pipe(tmp))
			return (1);
		if (check_greats(tmp))
			return (1);
		if (check_less(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	close_pipes(int *heredoc_pipe, int *signal_pipe)
{
	close(heredoc_pipe[1]);
	close(signal_pipe[1]);
	close(signal_pipe[0]);
}
