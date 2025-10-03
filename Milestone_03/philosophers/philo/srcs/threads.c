/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:02:00 by avolpini          #+#    #+#             */
/*   Updated: 2025/10/02 22:02:00 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->rules.n_philos)
	{
		if (pthread_create(&t->philos[i].thread, NULL,
				philo_routine, &t->philos[i]) != 0)
		{
			set_dead(t);
			while (--i >= 0)
				pthread_join(t->philos[i].thread, NULL);
			return (set_error("Error: pthread_create philo"));
		}
		i++;
	}
	return (0);
}

int	join_threads(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->rules.n_philos)
	{
		if (pthread_join(t->philos[i].thread, NULL) != 0)
			return (set_error("Error: pthread_join philo"));
		i++;
	}
	return (0);
}
