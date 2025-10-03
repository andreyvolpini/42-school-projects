/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:55:38 by avolpini          #+#    #+#             */
/*   Updated: 2025/10/02 17:55:38 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static int	parse(int ac, char **av, t_rules *r);

int	main(int ac, char **av)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (parse(ac, av, &table.rules) != 0)
		return (1);
	if (init_table(&table) != 0)
		return (1);
	if (start_threads(&table) != 0)
		return (table_destroy(&table), 1);
	if (start_monitor(&table) != 0)
	{
		set_dead(&table);
		join_threads(&table);
		table_destroy(&table);
		return (1);
	}
	if (join_monitor(&table) != 0)
		set_dead(&table);
	if (join_threads(&table) != 0)
		return (table_destroy(&table), 1);
	table_destroy(&table);
	return (0);
}

static int	parse(int ac, char **av, t_rules *r)
{
	if (ac != 5 && ac != 6)
		return (set_error("Use: ./philo philos time_to_die time_to_eat "
				"time_to_sleep [must_eat]"));
	if (!ft_atoi_safe(av[1], &r->n_philos)
		|| !ft_atoi_safe(av[2], &r->time_to_die)
		|| !ft_atoi_safe(av[3], &r->time_to_eat)
		|| !ft_atoi_safe(av[4], &r->time_to_sleep))
		return (set_error("Error: invalid numeric argument"));
	r->must_eat = -1;
	r->has_must_eat = false;
	if (ac == 6)
	{
		if (!ft_atoi_safe(av[5], &r->must_eat))
			return (set_error("Error: invalid must_eat"));
		r->has_must_eat = true;
	}
	if (r->n_philos < 1)
		return (set_error("Error: n_philos should to be >= 1"));
	if (r->time_to_die < 1 || r->time_to_eat < 1
		|| r->time_to_sleep < 1)
		return (set_error("Error: time should be to >= 1"));
	if (ac == 6 && r->must_eat < 1)
		return (set_error("Error: must_eat should to be >= 1"));
	return (0);
}

int	set_error(const char *s)
{
	while (*s)
		write(2, s++, 1);
	write(2, "\n", 1);
	return (1);
}
