/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:28:56 by avolpini          #+#    #+#             */
/*   Updated: 2025/10/02 18:28:56 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <limits.h>

#define NOT_SAFE 0
#define SAFE 1

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi_safe(const char *s, int *out)
{
	int			i;
	long long	n;

	i = 0;
	n = 0;
	if (!s || !s[i])
		return (NOT_SAFE);
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (NOT_SAFE);
		n = n * 10 + (s[i++] - '0');
		if (n > INT_MAX)
			return (NOT_SAFE);
	}
	if (n == 0)
		return (NOT_SAFE);
	*out = (int)n;
	return (SAFE);
}

long long	now_ms(void)
{
	struct timeval	tv;
	long long		sec;
	long long		usec;

	gettimeofday(&tv, NULL);
	sec = (long long)tv.tv_sec * 1000LL;
	usec = (long long)tv.tv_usec / 1000;
	return (sec + usec);
}
