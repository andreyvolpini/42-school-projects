#include "../../../push_swap.h"

void	swap(t_stack **stack)
{
	t_stack *first;
	t_stack *second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;// aponta o primeiro valor - (2) -> 1 -> NULL
	second = first->next;// aponta o segundo valor - 2 -> (1) -> NULL
	first->next = second->next;// aponta para o terceiro valor - 2 -> 1 -> (NULL)
	second->next = first;// aponta para o primeiro (2) -> 1 -> NULL
	*stack = second;// aponta para o segundo 2 -> (1) -> NULL
}

void do_sa(t_stack **a)
{
	swap(a);
	write(1, "sa\n", 3);
}

void do_sb(t_stack **b)
{
	swap(b);
	write(1, "sb\n", 3);
}

void do_ss(t_stack **a, t_stack **b)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
}
