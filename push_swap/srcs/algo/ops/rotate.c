#include "../../../push_swap.h"

void	rotate(t_stack **stack)
{
	t_stack *first;
	t_stack *last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;// aponta para o primeiro - (2) 3 1 NULL
	*stack = first->next;// aponta para o segundo valor - 2 (3) 1 NULL
	first->next = NULL;// quebra o laço, agora temos < *stack->[3]->[1] NULL > e < first->[2]->NULL > 
	last = *stack;// last = 3
	while (last->next)
		last = last->next; // até achar o final
	last->next = first; // retornamos o primeiro nó em first que é [2] - 3 1 (2) NULL
}

void	do_ra(t_stack **a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

void	do_rb(t_stack **b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

void	do_rr(t_stack **a, t_stack **b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
}