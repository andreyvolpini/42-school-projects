#include "../../../push_swap.h"

static void	push_chunck(t_stack **a, t_stack **b, int total_size);
static void	rotate_or_reverse(t_stack **a, t_stack **b, int min, int max);

void	chunk_sort(t_stack **a, t_stack **b, int total_size)
{
	push_chunck(a, b, total_size);
	push_back_sorted(a, b);
}

static void	push_chunck(t_stack **a, t_stack **b, int total_size)
{
	int		i;
	int		min;
	int		max;
	int		chunk_size;

	i= 0;
	min = 0;
	chunk_size = total_size / 6;
	max = chunk_size;
	while (*a)
	{
		if ((*a)->index >= min && (*a)->index < max)
		{
			do_pb(a, b);
			i++;
			if (i == chunk_size)
			{
				min += chunk_size;
				max += chunk_size;
				i = 0;
			}
		}
		else
			rotate_or_reverse(a, b, min, max);
	}
}

static void	rotate_or_reverse(t_stack **a, t_stack **b, int min, int max)
{
	t_stack *last;

	if (get_position_in_chunk(*a, min, max) <= (stack_size(*a) / 2))
	{
		if (*b && (*b)->next && (*b)->index < (*b)->next->index)
			do_rr(a, b);
		else
			do_ra(a);
	}
	else
	{
		last = get_last(*b);
		if (*b && last && last->index > (*b)->index)
			do_rrr(a, b);
		else
			do_rra(a);
	}
}
