#include "../../../push_swap.h"

/*
from = 12 4 3 NULL
to = 7 1 6 NULL
*/
void	push(t_stack **from, t_stack **to)
{
	t_stack *tmp;

	if (!from || !to)
		return ;
	tmp = *from;//aponta para 12
	*from = (*from)->next;//atualizamos from = 4 3 NULL
	tmp->next = *to;// tmp recebe to, tmp = 12 7 1 6 NULL
	*to = tmp;// to = 12 7 1 6 NULL
}

void	do_pa(t_stack **a, t_stack **b)
{
	push(b, a);
	write(1, "pa\n", 3);
}

void	do_pb(t_stack **a, t_stack **b)
{
	push(a, b);
	write(1, "pb\n", 3);
}
