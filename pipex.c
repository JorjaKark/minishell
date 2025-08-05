/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:15:11 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/15 15:47:03 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "pipex.h"

extern int	g_sig_num;
/*
void	writig_loop(int *fd, t_token *f)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, f->value, ft_strlen(line)) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
}

void	heredoc(t_token *op, t_token *f, t_minishell *mini)
{
	int		fd[2];
	pid_t	pid;

	(void)op;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		writig_loop(fd, f);
		close(fd[1]);
		free_everything(mini);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}*/

void	free_everything(t_minishell *mini)
{
	if (mini->line)
		free(mini->line);
	if (mini->token)
		free_tokens(mini->token);
	free_tree(mini->tree);
	free_s(mini->env_copy);
	free_pipes_pids(mini);
}
