/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:48:17 by avolpini          #+#    #+#             */
/*   Updated: 2025/10/02 18:48:17 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

#define MUTEX_OK 0
#define MUTEX_FAIL 1

static void	setup_philos(t_table *t);
static int	init_mutex(t_table *t);
static int	init_fork(t_table *t);

int	init_table(t_table *t)
{
	if (!t)
		return (set_error("Error: init_table with NULL"));
	t->philos = calloc(t->rules.n_philos, sizeof(t_philo));
	if (!t->philos)
		return (set_error("Error: malloc philos"));
	t->fork = calloc(t->rules.n_philos, sizeof(pthread_mutex_t));
	if (!t->fork)
	{
		free(t->philos);
		t->philos = NULL;
		return (set_error("Error: malloc forks"));
	}
	if (init_mutex(t) != MUTEX_OK)
	{
		free(t->philos);
		t->philos = NULL;
		free(t->fork);
		t->fork = NULL;
		return (MUTEX_FAIL);
	}
	t->someone_died = false;
	t->everyone_full = false;
	t->start_ms = now_ms();
	setup_philos(t);
	return (MUTEX_OK);
}

static int	init_mutex(t_table *t)
{
	if (pthread_mutex_init(&t->print_mutex, NULL) != MUTEX_OK)
		return (set_error("Error: pthread_mutex_init print_mutex"));
	if (pthread_mutex_init(&t->death_mutex, NULL) != MUTEX_OK)
	{
		pthread_mutex_destroy(&t->print_mutex);
		return (set_error("Error: pthread_mutex_init death_mutex"));
	}
	if (pthread_mutex_init(&t->meal_mutex, NULL) != MUTEX_OK)
	{
		pthread_mutex_destroy(&t->print_mutex);
		pthread_mutex_destroy(&t->death_mutex);
		return (set_error("Error: pthread_mutex_init meal_mutex"));
	}
	if (init_fork(t) != MUTEX_OK)
	{
		pthread_mutex_destroy(&t->print_mutex);
		pthread_mutex_destroy(&t->death_mutex);
		pthread_mutex_destroy(&t->meal_mutex);
		return (set_error("Error: pthread_mutex_init forks"));
	}
	return (MUTEX_OK);
}

static int	init_fork(t_table *t)
{
	int	i;
	int	j;

	i = 0;
	while (i < t->rules.n_philos)
	{
		if (pthread_mutex_init(&t->fork[i], NULL) != MUTEX_OK)
		{
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&t->fork[j++]);
			return (MUTEX_FAIL);
		}
		i++;
	}
	return (MUTEX_OK);
}

static void	setup_philos(t_table *t)
{
	int		i;
	int		n;
	t_philo	*p;

	i = 0;
	n = t->rules.n_philos;
	while (i < n)
	{
		p = &t->philos[i];
		p->id = i + 1;
		p->meals_eaten = 0;
		p->last_meal_ms = t->start_ms;
		p->fork_left = i;
		p->fork_right = (i + 1) % n;
		p->table = t;
		i++;
	}
}
