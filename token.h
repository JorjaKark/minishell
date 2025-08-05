/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erferrei <erferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:29:15 by erferrei          #+#    #+#             */
/*   Updated: 2024/10/16 17:53:56 by erferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft/libft.h"
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum				e_type
{
	OP,
	EXP
};

enum				e_subtype
{
	PIPE,
	LESS,
	GREAT,
	RLESS,
	RGREAT,
	CMD,
	ARG,
	FLAG
};

typedef struct s_expand
{
	int				i;
	int				j;
	int				k;
	char			*new_str;
	char			*var_name;
	char			*var_value;
}					t_expand;

typedef struct s_counter
{
	int				c;
	int				j;
	int				i;
	char			**new;
	int				flag;
}					t_counter;

typedef struct s_token
{
	char			*value;
	enum e_type		type;
	enum e_subtype	subtype;
	int				precedence;
	int				null;
	int				expand;
	char			*old_expd;
	struct s_token	*next;
	struct s_token	*prev;
	int				ambiguous;
}					t_token;

typedef struct s_vars
{
	int				i;
	int				a;
	int				count;
	int				m;
	char			quote;
	char const		*s;
	char			c;
	int				index;
}					t_vars;

int					count_words(char const *s, char c);
int					alloc_words(char const *s, char c, int index);
void				write_words(char **strstr, char const *s, char c,
						int index);
void				free_s(char **s);
char				**ft_split_m(char const *s, char c);

#endif