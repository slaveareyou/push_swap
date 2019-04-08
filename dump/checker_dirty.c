/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_dirty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 12:03:34 by gdamion-          #+#    #+#             */
/*   Updated: 2019/04/07 17:33:54 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checker.h"

//gcc src/checker/checker.c  src/common/common.c -L. -lft

int			main(int argc, char **argv)
{
	t_lswap	*cmds;
	t_lswap	*stack_one;
	t_lswap *stack_two;

	stack_one = (t_lswap*)malloc(sizeof(t_list));
	cmds = (t_lswap*)malloc(sizeof(t_list));
	process_stack(&argc, &argv, stack_one); //читаем стэк чисел, проверияем на правильность
	read_instructions(cmds);
	result(cmds, stack_one, stack_two);
	return (0);
}

void		process_stack(int *argc, char ***argv,	t_lswap *nums)
{
	long long num;
	t_lswap	*nums_check;
	t_lswap *run;
	int i;

	i = 1;
	if (*argc < 2)
		error();
	run = nums;
	run->prev = NULL; //у первого элемента нет элемента до него (кэп)
	while (i < (*argc))
	{
		if (i > 1)
		{
			nums_check = run; //записываем данный элемент списка в буфер
			run = run->next; //переходим на следующий элемент
			run = (t_lswap*)malloc(sizeof(t_list));
			nums_check->next = run;
			run->prev = nums_check; //сохраняем связь с предыдущим элементом
		}
		num = ft_atoi_simple_big((*argv)[i]);
		if (num < -2147483648 || 2147483647 < num)//проверяем на то, действительно ли число вмещается в int
			error();
		if (i > 1)
		{
			nums_check = run->prev;
			while (nums_check->prev != NULL)//пока не дошли до самого конца стека, проверяем на дубликат
			{
				if (num == nums_check->num)
					error();
				nums_check = nums_check->prev;
			}
		}
		run->num = (int)num; //пишем нужное число
		i++;
	}
	run->next = NULL; //замыкаем список
}

int			read_instructions(t_lswap *cmds)
{
	char *buf;
	int cmd_type;
	t_lswap *cmds_buf;
	t_lswap *run;
	int i;

	i = 0;
	buf = NULL;
	run = cmds;
	run->prev = NULL;
	while(get_next_line(1, &buf) != 0)
	{
		!(cmd_type = check_intruction(buf)) ? error() : 1;
		if (i > 0)
		{
			cmds_buf = run; //записываем данный элемент списка в буфер
			run = run->next; //переходим на следующий элемент
			run = (t_lswap*)malloc(sizeof(t_list));
			cmds_buf->next = run;
			run->prev = cmds_buf; //сохраняем связь с предыдущим элементом
		}
		run->num = cmd_type; //пишем нужный номер команды
		i++;
	}
	run->next = NULL; //замыкаем список
	return (cmd_type);
}

int			check_intruction(const char *cmd)
{
	int a;

	a = 0;
	!ft_strcmp(cmd, "sa") ? (a = 1) : 1;
	!ft_strcmp(cmd, "sb") ? (a = 2) : 1;
	!ft_strcmp(cmd, "ss") ? (a = 3) : 1;
	!ft_strcmp(cmd, "pa") ? (a = 4) : 1;
	!ft_strcmp(cmd, "pb") ? (a = 5) : 1;
	!ft_strcmp(cmd, "ra") ? (a = 6) : 1;
	!ft_strcmp(cmd, "rb") ? (a = 7) : 1;
	!ft_strcmp(cmd, "rr") ? (a = 8) : 1;
	!ft_strcmp(cmd, "rra") ? (a = 9) : 1;
	!ft_strcmp(cmd, "rrb") ? (a = 10) : 1;
	!ft_strcmp(cmd, "rrr") ? (a = 11) : 1;
	return (a);
}

void		result(t_lswap *cmds, t_lswap *stack_one, t_lswap *stack_two)
{
	// t_lswap	*c;
	// t_lswap *stack;

	// c = cmds;
	// stack = stack_one;
	// ft_printf("\n\nBefore\n");
	// while (c != NULL)
	// {
	// 	ft_printf("%d ", c->num);
	// 	c = c->next;
	// }
	// ft_printf("|\n");
	// while (stack != NULL)
	// {
	// 	ft_printf("%d ", stack->num);
	// 	stack = stack->next;
	// }
	// ft_printf("|\n\n");

	while (cmds != NULL)
	{
		(cmds->num == 1) ? s_swap(&stack_one) : 1;
		(cmds->num == 2) ? s_swap(&stack_two) : 1;
		(cmds->num == 3) ? s_swap_both(&stack_one, &stack_two) : 1;
		(cmds->num == 4) ? s_push(&stack_one, &stack_two) : 1;
		(cmds->num == 5) ? s_push(&stack_two, &stack_one) : 1;
		(cmds->num == 6) ? s_rotate(&stack_one) : 1;
		(cmds->num == 7) ? s_rotate(&stack_two) : 1;
		(cmds->num == 8) ? s_rotate_both(&stack_one, &stack_two) : 1;
		(cmds->num == 9) ? s_rev_rotate(&stack_one) : 1;
		(cmds->num == 10) ? s_rev_rotate(&stack_two) : 1;
		(cmds->num == 11) ? s_rev_rotate_both(&stack_one, &stack_two) : 1;
		cmds = cmds->next;
	}

	// c = stack_two;
	// stack = stack_one;

	// ft_printf("After\n");
	//  ft_printf("A ");
	// while (stack != NULL)
	// {
	// 	ft_printf("%d ", stack->num);
	// 	stack = stack->next;
	// }
	//  ft_printf("|\nB ");
	// while (c != NULL)
	// {
	// 	ft_printf("%d ", c->num);
	// 	c = c->next;
	// }
	// ft_printf("|\n\n");

	if (stack_two != NULL)
		answer(0);
	while (stack_one->next != NULL)
	{
		if (stack_one->num > stack_one->next->num)
			answer(0);
		stack_one = stack_one->next;
	}
	answer(1);
}

void 		answer(_Bool var)
{
	var ? ft_printf("OK\n") : ft_printf("KO\n");
	exit(0);
 }