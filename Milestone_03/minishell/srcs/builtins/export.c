/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:53:05 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:53:05 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		export_print_sorted(t_env *env);
static t_env	**env_to_ptr_array(t_env *env, size_t n);
static void		print_export_array(t_env **arr, size_t n);

int	builtin_export(t_geral *geral, t_cmds *cmd)
{
	int	i;
	int	had_invalid;

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (1);
	if (!cmd->cmd[1])
		return (export_print_sorted(geral->sh.env));
	had_invalid = 0;
	i = 1;
	while (cmd->cmd[i])
	{
		if (exp_app_one(geral, cmd->cmd[i], &had_invalid))
			return (1);
		i++;
	}
	if (had_invalid)
		return (1);
	return (0);
}

static int	export_print_sorted(t_env *env)
{
	size_t	n;
	t_env	**arr;

	n = env_size(env);
	arr = env_to_ptr_array(env, n);
	if (!arr)
		return (1);
	if (n > 1)
		bubble_sort_env_array(arr, n);
	print_export_array(arr, n);
	free(arr);
	return (0);
}

static t_env	**env_to_ptr_array(t_env *env, size_t n)
{
	t_env	**arr;
	size_t	i;

	if (n == 0)
	{
		arr = malloc(sizeof(*arr));
		if (!arr)
			return (NULL);
		return (arr);
	}
	arr = malloc(sizeof(*arr) * n);
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	return (arr);
}

static void	print_export_array(t_env **arr, size_t n)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (i < n)
	{
		if (arr[i] && arr[i]->key)
		{
			if (arr[i]->value)
				printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
			else
				printf("declare -x %s\n", arr[i]->key);
		}
		i++;
	}
}
