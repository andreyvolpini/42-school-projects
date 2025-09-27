/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:52:53 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:52:53 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get_value(t_env *env, const char *key)
{
	t_env	*n;

	n = env_find(env, key);
	if (n)
		return (n->value);
	else
		return (NULL);
}

static t_env	*env_new(const char *key, const char *value)
{
	t_env	*n;

	n = malloc(sizeof(t_env));
	if (!n)
		return (NULL);
	n->key = ft_strdup(key);
	if (value)
		n->value = ft_strdup(value);
	else
		n->value = NULL;
	if (!n->key || (value && !n->value))
	{
		free(n->key);
		free(n->value);
		free(n);
		return (NULL);
	}
	n->next = NULL;
	return (n);
}

int	env_set(t_env **penv, const char *key, const char *value, int exported)
{
	t_env	*cur;
	char	*nv;

	(void)exported;
	if (!penv || !key)
		return (1);
	cur = env_find(*penv, key);
	if (cur)
	{
		if (!value)
			return (0);
		nv = ft_strdup(value);
		if (!nv)
			return (1);
		free(cur->value);
		cur->value = nv;
		return (0);
	}
	cur = env_new(key, value);
	if (!cur)
		return (1);
	cur->next = *penv;
	*penv = cur;
	return (0);
}

void	bubble_sort_env_array(t_env **arr, size_t n)
{
	size_t	i;
	size_t	j;
	t_env	*tmp;

	if (!arr || n < 2)
		return ;
	i = 0;
	while (i < (n - 1))
	{
		j = 0;
		while (j < (n - i - 1))
		{
			if (cmp_env_ptrs(&arr[j], &arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
