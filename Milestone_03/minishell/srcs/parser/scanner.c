/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:53:55 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:53:55 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(int c);
static void	skip_space(const char *s, size_t *i);

int	get_position_quote(const char *str, size_t *pos, t_range *r)
{
	t_quote	q;
	size_t	i;

	if (!str || !pos || !r)
		return (-1);
	i = *pos;
	skip_space(str, &i);
	if (!str[i])
		return (*pos = i, 0);
	r->start = i;
	q = NORMAL;
	while (str[i])
	{
		if (q == NORMAL && is_space((unsigned char)str[i]))
			break ;
		update_quote_state(&q, str[i]);
		i++;
	}
	r->end = i;
	skip_space(str, &i);
	*pos = i;
	return (1);
}

static int	is_space(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static void	skip_space(const char *s, size_t *i)
{
	while (s[*i] == ' ' || is_space(s[*i]))
		(*i)++;
}

int	is_str_whitespace(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_space((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}
