/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:29:08 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 17:53:17 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"
# include "token.h"
# include <fcntl.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_red
{
	t_token			*red_op;
	t_token			*red_file;
}					t_red;

typedef struct s_cmd
{
	t_token			*name;
	t_token			*args;
}					t_cmd;

typedef struct s_tree
{
	t_cmd			*cmd;
	t_red			*red;
	struct s_tree	*next;
	struct s_tree	*prev;
}					t_tree;

typedef struct s_temp
{
	t_token			*name_node;
	t_token			*args_node;
	t_token			*red_node;
}					t_temp;

typedef struct s_minishell
{
	char			*line;
	t_token			*token;
	t_tree			*tree;
	t_tree			*node;
	char			**env_copy;
	char			**cmd_arg;
	int				is_here;
	int				built_in;
	int				saved_stdin;
	int				saved_stdout;
	int				heredoc_fd;
	int				has_heredoc;
	t_token			*redirection;
	t_token			*redirection_f;
	int				num_pipes;
	t_tree			*current_node;
	int				**pipes;
	pid_t			*pids;
	int				flag_pipes;
	int				m_g_sig_num;
}					t_minishell;

#endif