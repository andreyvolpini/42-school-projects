/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:53:13 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:53:13 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_unset_key(t_env **penv, const char *key);

int	builtin_unset(t_geral *geral, t_cmds *cmd)
{
	int			i;
	char		*name;

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (1);
	if (!cmd->cmd[1])
		return (0);
	i = 1;
	while (cmd->cmd[i])
	{
		name = cmd->cmd[i];
		env_unset_key(&geral->sh.env, name);
		i++;
	}
	return (0);
}

static int	env_unset_key(t_env **penv, const char *key)
{
	t_env	*cur;
	t_env	*prev;
	size_t	len;

	if (!penv || !*penv || !key)
		return (0);
	prev = NULL;
	cur = *penv;
	len = ft_strlen(key) + 1;
	while (cur)
	{
		if (cur->key && !ft_strncmp(cur->key, key, len))
		{
			if (prev)
				prev->next = cur->next;
			else
				*penv = cur ->next;
			free(cur->key);
			free(cur->value);
			return (free(cur), 1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
