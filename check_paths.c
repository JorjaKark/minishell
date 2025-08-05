/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:26 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/08 19:16:37 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_path(char *env)
{
	char	*path;
	int		i;

	i = 0;
	path = "PATH=";
	while (env[i] && path[i])
	{
		if (env[i] != path[i])
			return (0);
		i++;
	}
	return (path[i] == '\0');
}

char	*get_paths(char *env_paths, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*cmd_path;

	i = 0;
	paths = ft_split(env_paths, ':');
	if (!env_paths || env_paths[0] == '\0')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (cmd_path && is_path_valid(cmd_path))
			return (free_paths(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

void	path_env(char **env, char **paths)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (is_path(env[i]))
		{
			*paths = ft_strdup(ft_strchr(env[i], '=') + 1);
			break ;
		}
		i++;
	}
}
