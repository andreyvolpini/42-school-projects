/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:52:25 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:52:25 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			env_size(t_env *env);
static char	*join_key_and_value(const char *key, const char *value);

char	**env_to_array(t_env *env)
{
	int		i;
	int		size;
	char	**arr;

	size = env_size(env);
	arr = ft_calloc(size + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i] = join_key_and_value(env->key, env->value);
		if (!arr[i])
			return (free_arr(arr), NULL);
		i++;
		env = env->next;
	}
	return (arr);
}

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

static char	*join_key_and_value(const char *key, const char *value)
{
	size_t	key_len;
	size_t	value_len;
	char	*s;

	if (!key)
		return (NULL);
	if (!value)
		value = "";
	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	s = malloc(key_len + 1 + value_len + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, key, key_len);
	s[key_len] = '=';
	ft_memcpy(s + key_len + 1, value, value_len);
	s[key_len + 1 + value_len] = '\0';
	return (s);
}

t_env	*env_node_from_entry(const char *entry)
{
	t_env	*node;
	char	*pos_equal;

	if (!entry)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	pos_equal = ft_strchr(entry, '=');
	if (pos_equal)
	{
		node->key = ft_substr(entry, 0, (int)(pos_equal - entry));
		node->value = ft_strdup(pos_equal + 1);
	}
	else
	{
		node->key = ft_strdup(entry);
		node->value = ft_strdup("");
	}
	if (!node->key || !node->value)
		return (free(node->key), free(node->value), free(node), NULL);
	node->next = NULL;
	return (node);
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}
