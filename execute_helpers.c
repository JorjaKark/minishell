/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:25:47 by erferrei          #+#    #+#             */
/*   Updated: 2024/09/10 20:25:48 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	to_argc(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	is_absolute_path(char *path)
{
	if (path[0] == '/')
		return (1);
	return (0);
}

int	is_executable(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	if ((st.st_mode & S_IXUSR) == 0 || !S_ISREG(st.st_mode))
		return (2);
	return (1);
}

char	**ft_str_arr_join(char *s1, char **s2)
{
	int		i;
	char	**new;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (ft_strstrlen(s2) + 2));
	if (!new)
		return (NULL);
	new[0] = ft_strdup(s1);
	while (s2[i])
	{
		new[i + 1] = ft_strdup(s2[i]);
		i++;
	}
	new[i + 1] = NULL;
	return (new);
}
