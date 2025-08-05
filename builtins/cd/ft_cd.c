/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:41:22 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 15:22:43 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	go_to_path_cd(char *path_type, char ***env_copy)
{
	char	*path;

	path = NULL;
	if (ft_strncmp(path_type, "home", 4) == 0
		&& ft_strlen(path_type) == 4)
	{
		path = get_env_var(*env_copy, "HOME");
		if (!path)
			return ;
	}
	else if (ft_strncmp(path_type, "previous", 8) == 0
		&& ft_strlen(path_type) == 8)
	{
		path = get_env_var(*env_copy, "OLDPWD");
		if (!path)
			return ;
	}
	else
		return ;
	if (chdir(path) != 0)
		return ;
	update_pwd(env_copy);
}

char	*ft_last_dir(char *pwd)
{
	char	**paths;
	char	*last;
	int		i;
	char	*ptr;

	paths = ft_split(pwd, '/');
	i = 0;
	while (paths[i])
		i++;
	if (i > 1)
	{
		last = create_last(paths);
		if (last != NULL)
		{
			ptr = last;
			ptr_to_last(&ptr, paths, i);
		}
	}
	else
		last = ft_strdup("/");
	free_paths_cd(paths);
	return (last);
}

void	too_points_case(char ***env_copy, t_minishell *mini)
{
	char	cwd[4096];
	int		ret;
	char	*last_dir;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		last_dir = ft_last_dir(cwd);
		if (last_dir)
		{
			ret = chdir(last_dir);
			free(last_dir);
			if (ret == 0)
			{
				update_pwd(env_copy);
				return ;
			}
		}
		impossible_to_execute(mini);
	}
	return ;
}

int	cd_directions(int argc, char **argv, char ***env_copy, t_minishell *mini)
{
	int	ret;

	ret = 0;
	if (argc == 1)
		go_to_path_cd("home", env_copy);
	else if (argc == 2 && ft_strncmp(argv[1], "-", 1) == 0
		&& ft_strlen(argv[1]) == 1)
		go_to_path_cd("previous", env_copy);
	else if (argc == 2 && ft_strncmp(argv[1], ".", 1) == 0
		&& ft_strlen(argv[1]) == 1)
		return (ret);
	else if (argc > 2)
		to_many_arguments(mini);
	else if (argc == 2 && ft_strncmp(argv[1], "..", 2) == 0
		&& ft_strlen(argv[1]) == 2)
		too_points_case(env_copy, mini);
	else
		ret = 1;
	return (ret);
}

void	ft_cd(int argc, char **argv, char ***env_copy, t_minishell *mini)
{
	int	ret;

	ret = cd_directions(argc, argv, env_copy, mini);
	if (ret)
	{
		ret = chdir(argv[1]);
		if (ret == 0)
		{
			update_pwd(env_copy);
			mini->m_g_sig_num = 0;
			return ;
		}
		no_such_file_or_directory(argv, mini);
	}
	return ;
}
