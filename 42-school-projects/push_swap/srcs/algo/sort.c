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
	if (first < second && second > third && third > first)//1 3 2 - 6 12 9
	{
		do_sa(a);//3 1 2
		do_ra(a);//1 2 3
	}
	else if (first > second && second < third && third > first)//2 1 3 - 9 6 12
		do_sa(a);
	else if (first < second && second > third && third < first)//2 3 1
		do_rra(a);
	else if (first > second && second < third && third < first)//3 1 2
		do_ra(a);
	else if (first > second && second > third)//3 2 1
	{
		do_sa(a);//2 3 1
		do_rra(a);//1 2 3
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
//	else if (count <= 100)
//		chunk_sort(a, b, count);
	else
		radix_sort(a, b);
}