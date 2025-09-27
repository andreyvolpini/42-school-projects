/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:53:33 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:53:33 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_name(const char *s, size_t *len)
{
	size_t	i;
	char	*res;

	if (!s || !(is_first_ok(s[0])))
	{
		if (len)
			*len = 0;
		return (NULL);
	}
	i = 1;
	while (s[i] && (is_rest_ok(s[i])))
		i++;
	if (len)
		*len = i;
	res = ft_substr(s, 0, i);
	return (res);
}

char	*append_str(char *dst, const char *src)
{
	char	*res;

	if (!src)
		src = "";
	if (!dst)
		return (ft_strdup(src));
	res = ft_strjoin(dst, src);
	free(dst);
	return (res);
}

char	*append_char(char *dst, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (append_str(dst, buf));
}

const char	*ctx_getenv(t_shell *sh, const char *name)
{
	const t_env	*e;
	int			name_len;

	if (!sh || !name)
		return (NULL);
	name_len = ft_strlen(name) + 1;
	e = sh->env;
	while (e)
	{
		if (e->key && (ft_strncmp(e->key, name, name_len) == 0))
			return (e->value);
		e = e->next;
	}
	return (NULL);
}

int	expand_word_step(t_expand_ctx *ctx)
{
	if (ctx->s[ctx->i] == '\'' || ctx->s[ctx->i] == '"')
		return (copy_quote_adv(ctx->s, ctx->out, &ctx->i, &ctx->q) < 0);
	if (ctx->s[ctx->i] == '$' && ctx->q != IN_SINGLE)
	{
		if (ctx->q == NORMAL && ctx->s[ctx->i + 1]
			&& (ctx->s[ctx->i + 1] == '"' || ctx->s[ctx->i + 1] == '\''))
			ctx->i++;
		if (ctx->s[ctx->i + 1] == '!' || ft_isdigit(ctx->s[ctx->i + 1]))
			ctx->i += 2;
		return (dollar_dispatch(ctx->s, ctx->out, &ctx->i, ctx->sh) < 0);
	}
	*ctx->out = append_char(*ctx->out, ctx->s[ctx->i++]);
	if (!*ctx->out)
		return (-1);
	return (0);
}
