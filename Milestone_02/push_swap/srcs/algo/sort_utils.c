/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:29:03 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 16:29:03 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

int	stack_size(t_stack *stack);

int	find_min_index(t_stack *stack)
{
	int	min;

	min = stack->index;
	while (stack)
	{
		if (stack->index < min)
			min = stack->index;
		stack = stack->next;
	}
	return (min);
}

void	move_min_to_top(t_stack **a, int min_index)
{
	int		pos;
	int		size;
	t_stack	*tmp;

	pos = 0;
	tmp = *a;
	while (tmp && tmp->index != min_index)
	{
		pos++;
		tmp = tmp->next;
	}
	size = stack_size(*a);
	if (pos <= size / 2)
	{
		while ((*a)->index != min_index)
			do_ra(a);
	}
	else
	{
		while ((*a)->index != min_index)
			do_rra(a);
	}
}

int	stack_size(t_stack *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		stack = stack->next;
		size++;
	}
	return (size);
}
