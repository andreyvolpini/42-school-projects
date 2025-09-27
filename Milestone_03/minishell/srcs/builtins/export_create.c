/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 08:43:48 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/26 08:43:48 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_name_only(t_geral *geral, const char *key);
static int	export_assign(t_geral *geral, const char *key, const char *value);
static int	export_append(t_geral *geral, const char *key, const char *value);

int	exp_app_one(t_geral *geral, char *arg, int *had_invalid)
{
	t_assign	assign;
	char		*keydup;
	int			rc;

	if (!is_valid_identifier(arg, 1))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (*had_invalid = 1, 0);
	}
	split_assign(arg, &assign);
	keydup = ft_substr(assign.name, 0, assign.name_len);
	if (!keydup)
		return (1);
	if (assign.op == NAME_ONLY)
		rc = export_name_only(geral, keydup);
	else if (assign.op == ASSIGN)
		rc = export_assign(geral, keydup, assign.value);
	else
		rc = export_append(geral, keydup, assign.value);
	free(keydup);
	if (rc)
		return (1);
	return (0);
}

static int	export_name_only(t_geral *geral, const char *key)
{
	return (env_set(&geral->sh.env, key, NULL, 1));
}

static int	export_assign(t_geral *geral, const char *key, const char *value)
{
	return (env_set(&geral->sh.env, key, value, 1));
}

static int	export_append(t_geral *geral, const char *key, const char *value)
{
	t_env	*cur;
	char	*joined;

	cur = env_find(geral->sh.env, key);
	if (cur && cur->value)
	{
		if (value)
			joined = ft_strjoin(cur->value, value);
		else
			joined = ft_strjoin(cur->value, "");
		if (!joined)
			return (1);
		if (env_set(&geral->sh.env, key, joined, 1))
			return (free(joined), 1);
		free(joined);
		return (0);
	}
	if (value)
		return (env_set(&geral->sh.env, key, value, 1));
	else
		return (env_set(&geral->sh.env, key, "", 1));
}
