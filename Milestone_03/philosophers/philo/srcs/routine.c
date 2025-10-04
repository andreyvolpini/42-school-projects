/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:11:48 by avolpini          #+#    #+#             */
/*   Updated: 2025/10/01 17:11:48 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	philo_routine_loop(t_table *t, t_philo *p);
static void	release_forks(t_philo *p);
static int	take_forks(t_philo *p);
static void	do_eat(t_philo *p);

void	*philo_routine(void *arg)
{
	t_philo	*p;
	t_table	*t;

	p = (t_philo *)arg;
	t = p->table;
	if (t->rules.n_philos == 1)
	{
		pthread_mutex_lock(&t->fork[p->fork_left]);
		print_state(t, p->id, MSG_FORK);
		go_sleep(t, t->rules.time_to_die + 1);
		pthread_mutex_unlock(&t->fork[p->fork_left]);
		return (NULL);
	}
	if (p->id % 2 == 0)
		usleep(1000);
	while (sim_running(t))
	{
		if (philo_routine_loop(t, p) != 0)
			return (NULL);
		print_state(t, p->id, MSG_SLEEP);
		go_sleep(t, t->rules.time_to_sleep);
		print_state(t, p->id, MSG_THINK);
		usleep(500);
	}
	return (NULL);
}

static int	philo_routine_loop(t_table *t, t_philo *p)
{
	if (t->rules.has_must_eat && get_meals(p) >= t->rules.must_eat)
		return (1);
	if (!take_forks(p))
		return (1);
	do_eat(p);
	release_forks(p);
	if (t->rules.has_must_eat && get_meals(p) >= t->rules.must_eat)
		return (1);
	return (0);
}

static int	take_forks(t_philo *p)
{
	int		fork_1;
	int		fork_2;
	int		left;
	int		right;
	t_table	*t;

	t = p->table;
	left = p->fork_left;
	right = p->fork_right;
	fork_1 = left;
	fork_2 = right;
	if (left < right)
	{
		fork_1 = right;
		fork_2 = left;
	}
	pthread_mutex_lock(&t->fork[fork_1]);
	if (!sim_running(t))
		return (pthread_mutex_unlock(&t->fork[fork_1]), 0);
	print_state(t, p->id, MSG_FORK);
	pthread_mutex_lock(&t->fork[fork_2]);
	if (!sim_running(t))
		return (pthread_mutex_unlock(&t->fork[fork_2]),
			pthread_mutex_unlock(&t->fork[fork_1]), 0);
	return (print_state(t, p->id, MSG_FORK), 1);
}

static void	do_eat(t_philo *p)
{
	t_table		*t;

	t = p->table;
	if (!sim_running(t))
		return ;
	set_last_meal_now(p);
	print_state(t, p->id, MSG_EAT);
	go_sleep(t, t->rules.time_to_eat);
	if (!sim_running(t))
		return ;
	inc_meal(p);
}

static void	release_forks(t_philo *p)
{
	int		fork_1;
	int		fork_2;
	int		left;
	int		right;
	t_table	*t;

	t = p->table;
	left = p->fork_left;
	right = p->fork_right;
	fork_1 = left;
	fork_2 = right;
	if (left < right)
	{
		fork_1 = right;
		fork_2 = left;
	}
	pthread_mutex_unlock(&t->fork[fork_2]);
	pthread_mutex_unlock(&t->fork[fork_1]);
}
