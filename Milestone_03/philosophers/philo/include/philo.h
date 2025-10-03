/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:56:25 by avolpini          #+#    #+#             */
/*   Updated: 2025/10/02 17:56:25 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>

/*-------------- mensagens --------------*/
# define MSG_FORK	"has taken a fork"
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"
# define MSG_DIED 	"died"

/*--------------- structs ---------------*/
typedef struct s_rules
{
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
	bool	has_must_eat;
}	t_rules;

struct	s_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				fork_right;
	int				fork_left;
	long long		last_meal_ms;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_mutex;		
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_t		monitor_thread;
	long long		start_ms;
	bool			someone_died;
	bool			everyone_full;
	t_philo			*philos;
	t_rules			rules;
}	t_table;

/*--------------- state.c ---------------*/
void		print_state(t_table *t, int id, const char *msg);
void		set_everyone_full(t_table *t);
bool		everyone_full(t_table *t);
bool		sim_running(t_table *t);
void		set_dead(t_table *t);

/*--------------- access.c --------------*/
void		set_last_meal_now(t_philo *p);
void		go_sleep(t_table *t, int ms);
long long	get_last_meal(t_philo *p);
int			get_meals(t_philo *p);
void		inc_meal(t_philo *p);

/*--------------- utils.c ---------------*/
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi_safe(const char *s, int *out);
long long	now_ms(void);

/*-------------- threads.c --------------*/
int			start_threads(t_table *t);
int			join_threads(t_table *t);

/*-------------- monitor.c --------------*/
int			start_monitor(t_table *t);
int			join_monitor(t_table *t);

/*-------------- routine.c --------------*/
void		*philo_routine(void *arg);

/*--------------- init.c ----------------*/
int			init_table(t_table *t);

/*--------------- table.c ---------------*/
void		table_destroy(t_table *t);

/*---------------- main.c ---------------*/
int			set_error(const char *s);

#endif