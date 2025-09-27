/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:53:40 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:53:40 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_word_do(const char *s, t_shell *sh, char **out);
int	dollar_dispatch(const char *s, char **out, size_t *i, t_shell *sh);

char	*expand_word(const char *s, t_shell *sh)
{
	char	*out;

	if (!s)
		return (NULL);
	out = ft_strdup("");
	if (!out)
		return (NULL);
	if (expand_word_do(s, sh, &out) < 0)
	{
		free(out);
		return (NULL);
	}
	return (out);
}

int	expand_word_do(const char *s, t_shell *sh, char **out)
{
	t_expand_ctx	ctx;

	ctx.s = s;
	ctx.sh = sh;
	ctx.out = out;
	ctx.q = NORMAL;
	ctx.i = 0;
	while (ctx.s[ctx.i])
	{
		if (expand_word_step(&ctx) < 0)
			return (-1);
	}
	return (0);
}

int	dollar_qmark(char **out, size_t *i, int last_status)
{
	char	*num;

	num = ft_itoa(last_status);
	if (!num)
		return (-1);
	*out = append_str(*out, num);
	free(num);
	if (!*out)
		return (-1);
	*i += 2;
	return (0);
}

int	dollar_name(const char *s, char **out, size_t *i, t_shell *sh)
{
	size_t		len;
	char		*name;
	const char	*val;

	name = extract_name(s + *i + 1, &len);
	if (len == 0)
	{
		*out = append_char(*out, '$');
		if (!*out)
			return (-1);
		return ((*i)++, 0);
	}
	val = ctx_getenv(sh, name);
	if (val)
	{
		*out = append_str(*out, val);
		if (!*out)
			return (free(name), -1);
	}
	*i += 1 + len;
	return (free(name), 1);
}

int	dollar_dispatch(const char *s, char **out, size_t *i, t_shell *sh)
{
	int	ls;

	if (s[*i] != '$')
		return (0);
	if (s[*i + 1] == '?')
	{
		if (sh)
			ls = sh->g_status;
		else
			ls = 0;
		return (dollar_qmark(out, i, ls));
	}
	return (dollar_name(s, out, i, sh));
}
