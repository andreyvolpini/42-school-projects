#include "../../../push_swap.h"

void	reverse_rotate(t_stack **stack)
{
	t_stack *prev;
	t_stack *last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	prev = NULL;
	last = *stack;// aponta para o primeiro - (3) 2 1 NULL
	while (last->next)
	{
		prev = last;//aponta para um anterior - 3 (2) 1 NULL
		last = last->next;//aponta para o ultimo - 3 2 (1) NULL
	}
	prev->next = NULL;//quebra o laço, agora temos < *stack->[3]->[2] NULL > e < last->[1]->NULL > 
	last->next = *stack;//devolvo *stack para a direita de last
	*stack = last;//retorno tudo para *stack
}

void	do_rra(t_stack **a)
{
	reverse_rotate(a);
	write(1, "rra\n", 4);
}

void	do_rrb(t_stack **b)
{
	reverse_rotate(b);
	write(1, "rra\n", 4);
}

void	do_rrr(t_stack **a, t_stack **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	write(1, "rrr\n", 4);
}