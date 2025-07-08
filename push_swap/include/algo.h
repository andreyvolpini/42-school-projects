#ifndef ALGO_H
# define ALGO_H

# include "../push_swap.h"

//ops
void 	do_sa(t_stack **a);
void 	do_sa(t_stack **b);
void 	do_ss(t_stack **a, t_stack **b);

void	do_ra(t_stack **a);
void	do_rb(t_stack **b);
void	do_rr(t_stack **a, t_stack **b);

void	do_rra(t_stack **a);
void	do_rrb(t_stack **b);
void	do_rrr(t_stack **a, t_stack **b);

void	do_pa(t_stack **a, t_stack **b);
void	do_pb(t_stack **a, t_stack **b);

//sort
int		find_min_index(t_stack *stack);
void	move_min_to_top(t_stack **a, int min_index);
int		stack_size(t_stack *stack);
void	to_choose(t_stack **a, t_stack **b, int count);

void	sort_2(t_stack **a);
void	sort_3(t_stack **a);
void	sort_5(t_stack **a, t_stack **b);

void	radix_sort(t_stack **a, t_stack **b);
void	chunk_sort(t_stack **a, t_stack **b, int total_size);

int	get_max_index(t_stack *stack);
void	push_back_sorted(t_stack **a, t_stack **b);
int	get_position(t_stack *stack, int target_index);
int	get_position_in_chunk(t_stack *a, int min, int max);
t_stack	*get_last(t_stack *stack);

#endif