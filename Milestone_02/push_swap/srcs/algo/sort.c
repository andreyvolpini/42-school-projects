/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:28:55 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 16:28:55 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

void	sort_2(t_stack **a)
{
	int	first;
	int	second;

	first = (*a)->index;
	second = (*a)->next->index;
	if (first > second)
		do_sa(a);
}

void	sort_3(t_stack **a)
{
	int	first;
	int	second;
	int	third;

	first = (*a)->index;
	second = (*a)->next->index;
	third = (*a)->next->next->index;
	if (first < second && second > third && third > first)
	{
		do_sa(a);
		do_ra(a);
	}
	else if (first > second && second < third && third > first)
		do_sa(a);
	else if (first < second && second > third && third < first)
		do_rra(a);
	else if (first > second && second < third && third < first)
		do_ra(a);
	else if (first > second && second > third)
	{
		do_sa(a);
		do_rra(a);
	}
}

void	sort_5(t_stack **a, t_stack **b)
{
	int	i;
	int	min_index;

	i = 0;
	while (i < 2)
	{
		min_index = find_min_index(*a);
		move_min_to_top(a, min_index);
		do_pb(a, b);
		i++;
	}
	if (stack_size(*a) == 3)
		sort_3(a);
	else
		sort_2(a);
	do_pa(a, b);
	do_pa(a, b);
	if ((*a)->index > (*a)->next->index)
		do_sa(a);
}

void	to_choose(t_stack **a, t_stack **b, int count)
{
	if (count == 2)
		sort_2(a);
	else if (count == 3)
		sort_3(a);
	else if (count <= 5)
		sort_5(a, b);
	else if (count <= 100)
		chunk_sort(a, b, count);
	else
		radix_sort(a, b);
}
