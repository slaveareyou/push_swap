/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 12:04:35 by gdamion-          #+#    #+#             */
/*   Updated: 2019/04/15 18:31:46 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "../lib/includes/libft.h"
# include "../lib/includes/printf.h"
# include "../lib/includes/gnl.h"

typedef struct		s_lswap
{
	int				num;
	int				step1;
	int				step2;
	char			vec1;
	char			vec2;

	struct s_lswap	*next;
	struct s_lswap	*prev;
}					t_lswap;

void				error();
long long			ft_atoi_simple_big();

void				add_next(t_lswap **curr);
int					process_stack(int *argc, char ***argv, t_lswap *nums);
void				foreach_arg(t_lswap **nums, char **curr_arg, int *i);
void				add_el_and_check(t_lswap **nums, long long num);

int					s_swap(t_lswap **s, int stack_n, int mode);
int					s_swap_both(t_lswap **s1, t_lswap **s2, int mode);
int					s_push(t_lswap **s1, t_lswap **s2, int stack_n, int mode);
int					s_rotate(t_lswap **s, int stack_n, int mode);
int					s_rotate_both(t_lswap **s1, t_lswap **s2, int mode);
int					s_rev_rotate(t_lswap **s, int stack_n, int mode);
int					s_rev_rotate_both(t_lswap **s1, t_lswap **s2, int mode);

#endif
