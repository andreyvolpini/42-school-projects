/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:03:32 by avolpini          #+#    #+#             */
/*   Updated: 2025/10/01 18:03:32 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	table_destroy(t_table *t)
{
	int	i;

	if (!t)
		return ;
	if (t->fork)
	{
		i = 0;
		while (i < t->rules.n_philos)
			pthread_mutex_destroy(&t->fork[i++]);
		free(t->fork);
		t->fork = NULL;
	}
	pthread_mutex_destroy(&t->meal_mutex);
	pthread_mutex_destroy(&t->death_mutex);
	pthread_mutex_destroy(&t->print_mutex);
	if (t->philos)
	{
		free(t->philos);
		t->philos = NULL;
	}
}
