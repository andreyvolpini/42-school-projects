/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:52:34 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:52:34 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoll(const char *s, long long *out)
{
	int					sign;
	unsigned int		digit;
	unsigned long long	acum;
	unsigned long long	lim;

	sign = 1;
	acum = 0;
	lim = (unsigned long long)LLONG_MAX;
	if (!s || !out || !init_parse(&s, &sign))
		return (0);
	if (sign < 0)
		lim = (unsigned long long)LLONG_MAX + 1ULL;
	while (*s && ft_isdigit((unsigned char)*s))
	{
		digit = (unsigned)(*s - '0');
		if (acum > (lim - digit) / 10ULL)
			return (0);
		acum = acum * 10ULL + digit;
		s++;
	}
	if (*s != '\0')
		return (0);
	if (sign < 0)
		return (negative_parse(acum, out));
	return (*out = (long long)acum, 1);
}

int	init_parse(const char **ps, int *sign)
{
	const char	*s;

	if (!ps || !*ps || !**ps || !sign)
		return (0);
	s = *ps;
	*sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			*sign = -1;
		s++;
	}
	if (!ft_isdigit((unsigned char)*s))
		return (0);
	*ps = s;
	return (1);
}

int	negative_parse(unsigned long long acum, long long *out)
{
	unsigned long long	edge;

	if (!out)
		return (0);
	edge = (unsigned long long)LLONG_MAX + 1ULL;
	if (acum > edge)
		return (0);
	if (acum == edge)
		*out = LLONG_MIN;
	else
		*out = -(long long)acum;
	return (1);
}
