/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 07:27:54 by avolpini          #+#    #+#             */
/*   Updated: 2025/10/03 07:27:54 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	*monitor_routine(void *arg);
static int	all_full(t_table *t);

int	start_monitor(t_table *t)
{
	if (pthread_create(&t->monitor_thread, NULL, monitor_routine, t) != 0)
		return (set_error("Error: pthread_create monitor"));
	return (0);
}

int	join_monitor(t_table *t)
{
	if (pthread_join(t->monitor_thread, NULL) != 0)
		return (set_error("Error: pthread_join monitor"));
	return (0);
}

static void	*monitor_routine(void *arg)
{
	int			i;
	long long	last;
	long long	alive;
	t_table		*t;

	t = (t_table *)arg;
	while (sim_running(t))
	{
		i = -1;
		while (++i < t->rules.n_philos && sim_running(t))
		{
			last = get_last_meal(&t->philos[i]);
			alive = now_ms() - last;
			if (alive >= t->rules.time_to_die)
			{
				set_dead(t);
				return (print_state(t, t->philos[i].id, MSG_DIED), NULL);
			}
		}
		if (all_full(t))
			return (set_everyone_full(t), NULL);
		usleep(500);
	}
	return (NULL);
}

static int	all_full(t_table *t)
{
	int	i;
	int	n;

	if (t->rules.has_must_eat == false)
		return (0);
	i = 0;
	n = t->rules.n_philos;
	while (i < n)
	{
		if (get_meals(&t->philos[i]) < t->rules.must_eat)
			return (0);
		i++;
	}
	return (1);
}
