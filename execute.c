/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:15:01 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 15:25:38 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_sig_num;

void	ft_builtin(int argc, char **cmd, t_minishell *mini)
{
	(void)mini;
	//mini->m_g_sig_num = 0;
	if (!ft_strncmp(cmd[0], "cd", 3))
		ft_cd(argc, cmd, &mini->env_copy, mini);
	else if (!ft_strncmp(cmd[0], "echo", 5))
	{
		mini->m_g_sig_num = 0;
		ft_echo(argc, cmd);
	}
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd(argc, cmd, mini);
	else if (!ft_strncmp(cmd[0], "export", 7))
		ft_export(argc, cmd, &mini->env_copy, mini);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		ft_unset(argc, cmd, &mini->env_copy, mini);
	else if (!ft_strncmp(cmd[0], "env", 4))
		ft_env(argc, &mini->env_copy, mini);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ft_exit(argc, cmd, mini);
}

int	check_bytes(int fd, unsigned char *buffer, ssize_t bytes_read, ssize_t i)
{
	while (i < bytes_read)
	{
		if (buffer[i] < 32 && buffer[i] != '\n' && buffer[i] != '\r'
			&& buffer[i] != '\t')
		{
			close(fd);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_binary_file(char *path)
{
	int				fd;
	unsigned char	buffer[10];
	ssize_t			bytes_read;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (check_bytes(fd, buffer, bytes_read, 0))
			return (1);
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	if (bytes_read == -1)
	{
		perror("read");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	execute_helper(char **cmd, t_minishell *mini, char *valid_path,
		char *paths)
{
	if (is_absolute_path(cmd[0]))
	{
		free(paths);
		exec_absolute(valid_path, cmd, mini->env_copy, mini);
		return ;
	}
	if (cmd[0][0] == '.' && cmd[0][1] == '/')
	{
		free(paths);
		exec_executable(valid_path, cmd, mini->env_copy, mini);
		return ;
	}
}

void	execute(char **cmd, char **env, t_minishell *mini)
{
	char	*valid_path;
	char	*paths;
	int		argc;

	valid_path = NULL;
	paths = NULL;
	argc = to_argc(cmd);
	if (ft_check_cmd(cmd))
		return ;
	path_env(env, &paths);
	if (is_builtin(cmd[0]))
	{
		free(paths);
		ft_builtin(argc, cmd, mini);
		return ;
	}
	execute_helper(cmd, mini, valid_path, paths);
	ft_check_path(paths, cmd, mini);
	valid_path = get_paths(paths, cmd[0]);
	free(paths);
	ft_check_valid(valid_path, cmd, mini);
	e_execve_c(valid_path, cmd, env, mini);
}
