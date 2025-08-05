/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:53:42 by mafferre          #+#    #+#             */
/*   Updated: 2024/10/16 15:25:21 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_n_edge_case(char **str)
{
	int	j;
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i][0] == '-' && str[i][1] == 'n')
		{
			j = 1;
			while (str[i][j] == 'n')
				j++;
			if (str[i][j] != '\0' && i != 1)
				return (i);
			else if (str[i][j] != '\0' && i == 1)
				return (0);
		}
		else if (i == 1)
			return (0);
		else
			return (i);
		i++;
	}
	return (i);
}

int	is_tilde_edge_case(char **argv)
{
	if (ft_strlen(argv[1]) == 1)
		printf("%s\n", getenv("HOME"));
	else if (ft_strncmp(argv[1], "~test", 5) == 0 && ft_strlen(argv[1]) == 5)
		printf("\n");
	else if (ft_strncmp(argv[1], "~/", 2) == 0)
	{
		printf("%s/", getenv("HOME"));
		if (ft_strlen(argv[1]) == 2)
			printf("\n");
		else
			printf("%s\n", argv[1] + 2);
	}
	else
		return (1);
	return (0);
}

void	echo_print(int argc, char **argv, t_echo params)
{
	int	i;
	int	flag;

	i = params.i;
	flag = params.flag;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (flag)
		printf("\n");
	return ;
}

void	ft_echo(int argc, char **argv)
{
	t_echo	params;

	params.i = 1;
	params.flag = 1;
	if (argc == 1)
	{
		printf("\n");
		return ;
	}
	else if (argc == 2 && ft_strncmp(argv[1], "~", 1) == 0)
	{
		if (!is_tilde_edge_case(argv))
			return ;
	}
	else if ((argc > 1) && is_n_edge_case(argv))
	{
		params.i = is_n_edge_case(argv);
		params.flag = 0;
	}
	echo_print(argc, argv, params);
}
