/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:53:46 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:53:46 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_char_and_update_quote(const char *cmd, int i, t_norm_ctx *ctx);
static int	handle_operators(const char *cmd, int i, t_norm_ctx *ctx);
static char	*alloc_cmd_buffer(const char *cmd);
static int	is_op(const char c);

char	*normalize_cmd(const char *cmd)
{
	int			i;
	int			j;
	t_quote		q;
	char		*new_cmd;
	t_norm_ctx	ctx;

	if (!cmd)
		return (NULL);
	new_cmd = alloc_cmd_buffer(cmd);
	if (!new_cmd)
		return (NULL);
	i = 0;
	j = 0;
	q = NORMAL;
	ctx = (t_norm_ctx){new_cmd, &j, &q};
	while (cmd[i])
	{
		if (q == NORMAL && is_op(cmd[i]))
			i = handle_operators(cmd, i, &ctx);
		else
			i = copy_char_and_update_quote(cmd, i, &ctx);
	}
	if (q != NORMAL)
		return (free(new_cmd), NULL);
	return (new_cmd[j] = '\0', new_cmd);
}

static char	*alloc_cmd_buffer(const char *cmd)
{
	int		len;
	char	*buffer;

	if (!cmd)
		return (NULL);
	len = ft_strlen(cmd);
	buffer = malloc(sizeof(char) * (len * 3 + 1));
	if (!buffer)
		return (NULL);
	return (buffer);
}

static int	copy_char_and_update_quote(const char *cmd, int i, t_norm_ctx *ctx)
{
	char	c;

	c = cmd[i];
	ctx->new_cmd[(*ctx->j)++] = c;
	update_quote_state(ctx->q, c);
	return (i + 1);
}

static int	handle_operators(const char *cmd, int i, t_norm_ctx *ctx)
{
	if (*ctx->j > 0 && ctx->new_cmd[*ctx->j - 1] != ' ')
		ctx->new_cmd[(*ctx->j)++] = ' ';
	ctx->new_cmd[(*ctx->j)++] = cmd[i];
	if ((cmd[i] == '<' || cmd[i] == '>') && cmd[i + 1] == cmd[i])
		ctx->new_cmd[(*ctx->j)++] = cmd[++i];
	if (cmd[i + 1] && cmd[i + 1] != ' ')
		ctx->new_cmd[(*ctx->j)++] = ' ';
	return (i + 1);
}

static int	is_op(const char c)
{
	return (c == '|' || c == '<' || c == '>');
}
