/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 07:31:35 by avolpini          #+#    #+#             */
/*   Updated: 2025/10/03 07:31:35 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

bool	sim_running(t_table *t)
{
	bool	should_stop;

	pthread_mutex_lock(&t ->death_mutex);
	should_stop = t->someone_died || t->everyone_full;
	pthread_mutex_unlock(&t->death_mutex);
	return (!should_stop);
}

void	set_dead(t_table *t)
{
	pthread_mutex_lock(&t->death_mutex);
	t->someone_died = true;
	pthread_mutex_unlock(&t->death_mutex);
}

void	set_everyone_full(t_table *t)
{
	pthread_mutex_lock(&t->death_mutex);
	t->everyone_full = true;
	pthread_mutex_unlock(&t->death_mutex);
}

bool	everyone_full(t_table *t)
{
	bool	full;

	pthread_mutex_lock(&t->death_mutex);
	full = t->everyone_full;
	pthread_mutex_unlock(&t->death_mutex);
	return (full);
}

void	print_state(t_table *t, int id, const char *msg)
{
	bool	running;

	running = sim_running(t);
	pthread_mutex_lock(&t->print_mutex);
	if ((ft_strcmp(msg, MSG_DIED) != 0)
		&& !running)
	{
		pthread_mutex_unlock(&t->print_mutex);
		return ;
	}
	printf("%lld %d %s\n", now_ms() - t->start_ms, id, msg);
	pthread_mutex_unlock(&t->print_mutex);
}
