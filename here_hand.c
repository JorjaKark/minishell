/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_hand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:07 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 17:25:39 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

int	wait_here(int *heredoc_pipe, int *signal_pipe, pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(heredoc_pipe[1]);
	waitpid(pid, &status, 0);
	if ((WIFEXITED(status) && WEXITSTATUS(status) != 0) || WIFSIGNALED(status))
	{
		g_sig_num = WEXITSTATUS(status) - 128;
		close(heredoc_pipe[0]);
		close(signal_pipe[1]);
		close(signal_pipe[0]);
		return (-1);
	}
	return (0);
}

int	check_end(char *line, t_token *redirection_f)
{
	char	*old;

	if (redirection_f->old_expd == NULL && line[0] != '\0' && ft_strncmp(line,
			redirection_f->value, ft_strlen(line)) == 0)
	{
		free(line);
		return (1);
	}
	if (redirection_f->old_expd)
	{
		old = remove_quotes_old(redirection_f->old_expd);
		//printf("old: %s\n", old);
		if (line[0] != '\0' && ft_strncmp(line, old, ft_strlen(line)) == 0)
		{
			free(line);
			free(old);
			return (1);
		}
		else if (line[0] == '\0' && old[0] == '\0')
		{
			free(line);
			free(old);
			return (1);
		}
		free(old);
	}
	return (0);
}

void	write_free_line(char *line, int *heredoc_pipe)
{
	write(heredoc_pipe[1], line, ft_strlen(line));
	write(heredoc_pipe[1], "\n", 1);
	free(line);
}

void	line_loop(t_minishell *mini, t_token *redirection_f, int *heredoc_pipe,
		int *signal_pipe)
{
	char	*line;
	int		flag;

	signal(SIGINT, ctrlc_here);
	close(heredoc_pipe[0]);
	close(signal_pipe[0]);
	line = readline("> ");
	while (line != NULL)
	{
		if (check_end(line, redirection_f))
			break ;
		flag = 1;
		line = expand_var(line, mini->env_copy, &flag, mini);
		write_free_line(line, heredoc_pipe);
		line = readline("> ");
	}
	close_pipes(heredoc_pipe, signal_pipe);
	if (line == NULL)
	{
		write(STDERR_FILENO, "warning: here-document ", 23);
		printf("delimited by end-of-file (wanted `%s')\n",
			redirection_f->value);
	}
	free_here(mini);
	exit(0);
}

int	handle_heredoc(t_token *redirection, t_token *redirection_f,
		t_minishell *mini)
{
	int		heredoc_pipe[2];
	int		signal_pipe[2];
	pid_t	pid;

	(void)redirection;
	if (pipe(heredoc_pipe) == -1 || pipe(signal_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		line_loop(mini, redirection_f, heredoc_pipe, signal_pipe);
	else if (wait_here(heredoc_pipe, signal_pipe, pid) == -1)
		return (-1);
	close(signal_pipe[1]);
	close(signal_pipe[0]);
	close(heredoc_pipe[1]);
	return (heredoc_pipe[0]);
}
