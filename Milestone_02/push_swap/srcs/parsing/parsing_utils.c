/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:32:35 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 16:32:35 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

int	is_valid_number(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	sort_array(int *sorted, int count)
{
	int	i;
	int	tmp;
	int	sort;

	sort = 0;
	while (!sort)
	{
		i = 0;
		sort = 1;
		while (i < count - 1)
		{
			if (sorted[i] > sorted[i + 1])
			{
				sort = 0;
				tmp = sorted[i];
				sorted[i] = sorted[i + 1];
				sorted[i + 1] = tmp;
			}
			i++;
		}
	}
}

// verifica se a entrada já está ordenada
int	is_sorted(int *original, int *sorted, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (original[i] != sorted[i])
			return (0);
		i++;
	}
	return (1);
}

// descobrir o index de cada número ordenado
int	get_index(int *sorted, int count, int value)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (sorted[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

// dar free no stack caso alguma falha
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}
