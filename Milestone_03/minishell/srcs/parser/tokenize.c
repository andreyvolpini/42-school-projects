/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:54:17 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:54:17 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_tk_rang(t_token **list, const char *norm, t_range r, t_shell *sh);

t_token	*tokenize(const char *line, t_shell *sh)
{
	t_token	*list;
	char	*normalized;
	size_t	pos;
	t_range	r;

	if (!line)
		return (NULL);
	normalized = normalize_cmd(line);
	if (!normalized)
		return (NULL);
	list = NULL;
	pos = 0;
	while ((get_position_quote(normalized, &pos, &r)) == 1)
	{
		if ((add_tk_rang(&list, normalized, r, sh)) < 0)
		{
			free(normalized);
			if (list)
				free_tokens(list);
			return (NULL);
		}
	}
	free(normalized);
	return (list);
}

int	add_tk_rang(t_token **list, const char *norm, t_range r, t_shell *sh)
{
	char	*raw;
	int		in_s;
	int		in_d;
	int		ok;
	t_quote	quote;

	raw = ft_substr(norm, r.start, r.end - r.start);
	if (!raw)
		return (-1);
	detect_quote_flags(raw, &in_s, &in_d);
	ok = add_op_token(list, raw, in_s, in_d);
	if (ok == 1)
		return (free(raw), 0);
	else if (ok < 0)
		return (free(raw), -1);
	if (in_s)
		quote = IN_SINGLE;
	else if (in_d)
		quote = IN_DOUBLE;
	else
		quote = NORMAL;
	if (add_word_t(list, raw, sh, quote) < 0)
		return (free_tokens(*list), *list = NULL, free(raw), -1);
	return (free(raw), 0);
}
