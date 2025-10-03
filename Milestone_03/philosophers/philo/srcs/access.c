/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 08:29:10 by avolpini          #+#    #+#             */
/*   Updated: 2025/10/03 08:29:10 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	get_meals(t_philo *p)
{
	int	meals;

	pthread_mutex_lock(&p->table->meal_mutex);
	meals = p->meals_eaten;
	pthread_mutex_unlock(&p->table->meal_mutex);
	return (meals);
}

long long	get_last_meal(t_philo *p)
{
	long long	l_meal;

	pthread_mutex_lock(&p->table->meal_mutex);
	l_meal = p->last_meal_ms;
	pthread_mutex_unlock(&p->table->meal_mutex);
	return (l_meal);
}

void	inc_meal(t_philo *p)
{
	pthread_mutex_lock(&p->table->meal_mutex);
	p->meals_eaten++;
	pthread_mutex_unlock(&p->table->meal_mutex);
}

void	set_last_meal_now(t_philo *p)
{
	long long	now;

	now = now_ms();
	pthread_mutex_lock(&p->table->meal_mutex);
	p->last_meal_ms = now;
	pthread_mutex_unlock(&p->table->meal_mutex);
}

void	go_sleep(t_table *t, int ms)
{
	long long	target;

	target = now_ms() + ms;
	while (sim_running(t) && now_ms() < target)
		usleep(500);
}
