/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:28:30 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 16:28:30 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	free_all(t_stack *a, t_stack *b, int *o, int *s, char **v);
int	setup_stacks(t_stack **a, char ***v, int **o, int **s, int ac, char **av);
int	count_values(char **values);

int	main(int ac, char **av)
{
	t_stack *a;
	t_stack *b;
	int		*original;
	int		*sorted;
	char	**values;

	(void)av;
	a = NULL;
	b = NULL;
	if (ac < 2)
		return (0);
	if (!setup_stacks(&a, &values, &original, &sorted, ac, av))
		return (1);
	to_choose(&a, &b, count_values(values));
	free_all(a, b, original, sorted, values);
	return (0);
}

int	setup_stacks(t_stack **a, char ***v, int **o, int **s, int ac, char **av)
{
	int		count;
	char	*joined;

	joined = join_args(ac, av);
	if (!joined)
		return (ft_putstr_fd("Error\nMemory alloc <join_args>\n", 2), 0);
	*v = ft_split(joined, ' ');
	free(joined);
	if (!*v || !**v)
		return (ft_putstr_fd("Error\nSplit failed\n", 2), free_split(*v), 0);
	count = count_values(*v);
	*o = alloc_array(count, *v);
	if (!*o)
		return (free_split(*v), 0);
	*s = duplicate_and_sort(*o, count);
	if (!*s)
		return (ft_putstr_fd("Error\nDuplicate numbers\n", 2), free(*o), free_split(*v), 0);
	if (is_sorted(*o, *s, count))
		return (free(*o), free(*s), free_split(*v), 0);
	fill_stack(a, *o, *s, count);
	return (1);
}

int	count_values(char **values)
{
	int	count;

	count = 0;
	while (values[count])
		count++;
	return (count);
}

void	free_all(t_stack *a, t_stack *b, int *o, int *s, char **v)
{
	free_stack(&a);
	free_stack(&b);
	free(o);
	free(s);
	free_split(v);
}
