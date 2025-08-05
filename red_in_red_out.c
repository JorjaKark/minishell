/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in_red_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:04:13 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 14:59:13 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "pipex.h"

extern int	g_sig_num;

void	red_in(t_token *op, t_token *f, t_minishell *mini, int flag_here)
{
	int		file1;
	char	*file;

	file1 = 0;
	if (op != NULL)
	{
		file = f->value;
		if (access(file, F_OK) == -1)
		{
			ft_fprintf(file, "No such file or directory\n");
			free_and_exit(mini);
		}
		if (access(file, R_OK) == -1)
		{
			ft_fprintf(file, "Permission denied\n");
			free_and_exit(mini);
		}
		file1 = open(file, O_RDONLY);
		if (file1 == -1)
			fail_open_file(file, mini);
		if (flag_here)
			dup2(file1, 0);
		close(file1);
	}
}

int	red_in_built(t_token *op, t_token *f, t_minishell *mini, int flag_here)
{
	int		file1;
	char	*file;

	file1 = 0;
	if (op != NULL)
	{
		file = f->value;
		if (access(file, F_OK) == -1)
		{
			ft_fprintf(file, "No such file or directory\n");
			mini->m_g_sig_num = 1 - 128;
			return (1);
		}
		if (access(file, R_OK) == -1)
		{
			ft_fprintf(file, "Permission denied\n");
			mini->m_g_sig_num = 1 - 128;
			return (1);
		}
		file1 = open(file, O_RDONLY);
		if (file1 == -1)
			fail_open_file(file, mini);
		if (flag_here)
			dup2(file1, 0);
		close(file1);
	}
	return (0);
}

void	red_out(t_token *op, t_token *f, t_minishell *mini)
{
	int		file2;
	char	*file;

	file2 = 0;
	if (op != NULL)
	{
		file = f->value;
		if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		{
			ft_fprintf(file, "Permission denied\n");
			free_and_exit(mini);
		}
		if (op->subtype == GREAT)
			file2 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (op->subtype == RGREAT)
			file2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file2 == -1)
		{
			ft_fprintf(file, "Failed to open the file\n");
			free_and_exit(mini);
		}
		dup2(file2, 1);
		close(file2);
	}
}

int	red_out_built(t_token *op, t_token *f, t_minishell *mini)
{
	int		file2;
	char	*file;

	file2 = 0;
	if (op != NULL)
	{
		file = f->value;
		if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		{
			ft_fprintf(file, "Permission denied\n");
			mini->m_g_sig_num = 1 - 128;
			return (1);
		}
		if (op->subtype == GREAT)
			file2 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (op->subtype == RGREAT)
			file2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file2 == -1)
		{
			ft_fprintf(file, "Failed to open the file\n");
			mini->m_g_sig_num = 1 - 128;
			return (1);
		}
		dup2(file2, 1);
		close(file2);
	}
	return (0);
}
