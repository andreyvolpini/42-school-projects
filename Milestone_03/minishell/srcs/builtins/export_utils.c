/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:52:58 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:52:58 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_first_ok(int c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_rest_ok(int c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_identifier(const char *s, int allow_assign)
{
	size_t	i;

	i = 0;
	if (!s || !s[i] || s[i] == '=' || !is_first_ok((unsigned char)s[i]))
		return (0);
	while (s[++i])
	{
		if (allow_assign)
		{
			if (s[i] == '=')
				break ;
			if (s[i] == '+' && s[i + 1] == '=')
				break ;
		}
		if (!is_rest_ok((unsigned char)s[i]))
			return (0);
	}
	return (1);
}

void	split_assign(const char *arg, t_assign *out)
{
	const char	*equal;

	out->name = NULL;
	out->name_len = 0;
	out->value = NULL;
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		out->name = arg;
		out->name_len = ft_strlen(arg);
		out->value = NULL;
		out->op = NAME_ONLY;
		return ;
	}
	out->value = equal + 1;
	if (equal > arg && equal[-1] == '+')
	{
		out->name = arg;
		out->name_len = (size_t)((equal - 1) - arg);
		out->op = APPEND;
		return ;
	}
	out->name = arg;
	out->name_len = (size_t)(equal - arg);
	out->op = ASSIGN;
}

int	cmp_env_ptrs(const void *a, const void *b)
{
	const t_env	*ea;
	const t_env	*eb;
	size_t		len_a;
	size_t		len_b;
	size_t		n;

	ea = *(const t_env * const *)a;
	eb = *(const t_env * const *)b;
	len_a = 0;
	len_b = 0;
	if (ea->key)
		len_a = ft_strlen(ea->key);
	if (eb->key)
		len_b = ft_strlen(eb->key);
	if (len_a > len_b)
		n = len_a + 1;
	else
		n = len_b + 1;
	return (ft_strncmp(ea->key, eb->key, n));
}
