/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:53:50 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:53:50 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quote_state(t_quote *q, char c)
{
	if (*q == NORMAL)
	{
		if (c == '\'')
			*q = IN_SINGLE;
		else if (c == '"')
			*q = IN_DOUBLE;
	}
	else if (*q == IN_SINGLE && c == '\'')
		*q = NORMAL;
	else if (*q == IN_DOUBLE && c == '"')
		*q = NORMAL;
}

int	copy_quote_adv(const char *s, char **out, size_t *i, t_quote *q)
{
	char	c;

	c = s[*i];
	*out = append_char(*out, c);
	if (!*out)
		return (-1);
	update_quote_state(q, c);
	(*i)++;
	return (0);
}

int	has_unclosed_quotes(const char *line)
{
	int		i;
	t_quote	q;

	i = 0;
	q = NORMAL;
	while (line && line[i])
	{
		update_quote_state(&q, line[i]);
		i++;
	}
	return (q != NORMAL);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	handle_opers_errors(t_geral *geral)
{
	int	i;

	i = geral->geopers.n_erro;
	if ((access(geral->geopers.opers[i].value, F_OK) == 0)
		&& (access(geral->geopers.opers[i].value, R_OK) != 0))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(geral->geopers.opers[i].value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(geral->geopers.opers[i].value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	geral->sh.g_status = 1;
}
