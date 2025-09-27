/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:54:10 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:54:10 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_op_lex(const char *s)
{
	if (!s || !*s)
		return (0);
	else if (s[0] == '|' && s[1] == '\0')
		return (1);
	else if (s[0] == '<' && s[1] == '\0')
		return (1);
	else if (s[0] == '>' && s[1] == '\0')
		return (1);
	else if (s[0] == '<' && s[1] == '<' && s[2] == '\0')
		return (1);
	else if (s[0] == '>' && s[1] == '>' && s[2] == '\0')
		return (1);
	return (0);
}

static int	type_op(const char *s)
{
	if (s[0] == '|' && s[1] == '\0')
		return (T_PIPE);
	else if (s[0] == '<' && s[1] == '\0')
		return (T_IN);
	else if (s[0] == '>' && s[1] == '\0')
		return (T_OUT);
	else if (s[0] == '<' && s[1] == '<' && s[2] == '\0')
		return (T_HEREDOC);
	else
		return (T_APPEND);
}

int	add_op_token(t_token **list, const char *raw, int in_s, int in_d)
{
	t_token	*token;

	if (in_s || in_d || !is_op_lex(raw))
		return (0);
	token = new_token(NULL, type_op(raw), NORMAL);
	if (!token)
		return (-1);
	add_new_token(list, token);
	return (1);
}

static int	prev_is_heredoc(t_token *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	if (list->type == T_HEREDOC)
		return (1);
	return (0);
}

int	add_word_t(t_token **list, const char *raw, t_shell *sh, t_quote q)
{
	char	*exp;
	char	*clean;
	t_token	*token;

	if (!raw)
		return (-1);
	if (list && *list && prev_is_heredoc(*list))
		exp = ft_strdup(raw);
	else
		exp = expand_word(raw, sh);
	if (!exp)
		return (-1);
	clean = strip_outside_quotes(exp, ft_strlen(exp));
	free(exp);
	if (!clean)
		return (-1);
	token = new_token(clean, T_WORD, q);
	if (!token)
		return (free(clean), -1);
	add_new_token(list, token);
	free(clean);
	return (0);
}
