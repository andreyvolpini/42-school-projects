/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:52:29 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:52:29 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_cmds *cmd, t_env *env)
{
	if (cmd && cmd->cmd && cmd->cmd[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	while (env)
	{
		if (env->key)
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
			else
				printf("%s=\n", env->key);
		}
		env = env->next;
	}
	return (0);
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*last;
	t_env	*new;
	int		i;

	i = 0;
	head = NULL;
	last = NULL;
	while (envp && envp[i])
	{
		new = env_node_from_entry(envp[i]);
		if (!new)
			return (free_env_list(head), NULL);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return (head);
}

t_env	*env_find(t_env *env, const char *key)
{
	size_t	len;

	if (!key)
		return (NULL);
	len = ft_strlen(key) + 1;
	while (env)
	{
		if (env->key && ft_strncmp(env->key, key, len) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
