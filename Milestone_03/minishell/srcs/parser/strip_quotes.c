/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:53:59 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:53:59 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_char(t_quote *q, char c, char *out, size_t *j)
{
	if (*q == NORMAL)
	{
		if (c == '\'' || c == '"')
			update_quote_state(q, c);
		else
			out[(*j)++] = c;
	}
	else
	{
		if ((*q == IN_SINGLE && c == '\'') || (*q == IN_DOUBLE && c == '"'))
			update_quote_state(q, c);
		else
			out[(*j)++] = c;
	}
}

char	*strip_outside_quotes(const char *src, size_t len)
{
	t_quote	q;
	size_t	i;
	size_t	j;
	char	*out;

	out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	q = NORMAL;
	i = 0;
	j = 0;
	while (i < len)
	{
		process_char(&q, src[i], out, &j);
		i++;
	}
	if (q != NORMAL)
		return (free(out), NULL);
	out[j] = '\0';
	return (out);
}
