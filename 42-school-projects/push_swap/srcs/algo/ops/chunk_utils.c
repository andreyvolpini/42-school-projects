/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:30:31 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 16:30:31 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

int	get_max_index(t_stack *stack)
{
	int	max;

	max = stack ->index;
	while (stack)
	{
		if (stack-> index > max)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

void	push_back_sorted(t_stack **a, t_stack **b)
{
	int	max;

	while (*b)
	{
		max = get_max_index(*b);
		if ((*b)->index == max)
			do_pa(a, b);
		else if (get_position(*b, max) <= (stack_size(*b) / 2))
			do_rb(b);
		else
			do_rrb(b);
	}
}

int	get_position(t_stack *stack, int target_index)
{
	int	i;

	i = 0;
	while (stack)
	{
		if (stack->index == target_index)
			return (i);
		i++;
		stack = stack->next;
	}
	return (-1);
}

int	get_position_in_chunk(t_stack *a, int min, int max)
{
	int	pos;

	pos = 0;
	while (a)
	{
		if (a->index >= min && a->index < max)
			return (pos);
		pos++;
		a = a->next;
	}
	return (-1);
}

t_stack	*get_last(t_stack *stack)
{
	while (stack && stack->next)
		stack = stack->next;
	return (stack);
}
