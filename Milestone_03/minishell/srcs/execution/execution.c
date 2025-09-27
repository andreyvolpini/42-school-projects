/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:56:12 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/26 14:07:23 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_path(t_geral *geral, t_cmds *cmds, char *path, int i)
{
	cmds->path = ft_strdup(cmds->cmd[0]);
	if (path)
	{
		free(cmds->cmd[0]);
		cmds->cmd[0] = ft_substr(path,
				ft_strlen(geral->gecmds.path[i]), ft_strlen(path));
	}
}

int	cmds_test_utils(t_geral *geral, t_cmds *cmds, int i)
{
	char		*path;
	int			retorno;

	retorno = 0;
	path = ft_strjoin(geral->gecmds.path[i], cmds->cmd[0]);
	if (!path)
		retorno = 1;
	geral->vars.is_dir = is_directory(cmds);
	if (geral->vars.is_dir == 1)
		retorno = 3;
	else if (geral->vars.is_dir == 2)
		return (0);
	if (cmds->cmd[0] && ft_strchr(cmds->cmd[0], '/')
		&& (access(cmds->cmd[0], X_OK) == 0 && retorno != 3))
	{
		create_path(geral, cmds, path, i);
		retorno = 2;
	}
	else if (cmds->cmd[0] && ((cmds->cmd[0][0] != '.'
			&& cmds->cmd[0][0] != '/') && (access(path, X_OK) == 0)))
	{
		cmds->path = ft_strdup(path);
		retorno = 2;
	}
	return (free(path), retorno);
}

int	cmds_test(t_geral *geral, t_cmds *cmds)
{
	int		i;
	int		retorno;

	i = 0;
	while (geral->gecmds.path && geral->gecmds.path[i])
	{
		retorno = cmds_test_utils(geral, cmds, i);
		if (retorno == 2)
			return (0);
		else if (retorno == 1)
			return (1);
		i++;
	}
	if (ft_strncmp(geral->gecmds.path[0], "Error/", 7) == 0 && retorno != 3)
	{
		i--;
		if (cmds->cmd[i] && (access(cmds->cmd[i], X_OK) == 0))
		{
			create_path(geral, cmds, NULL, i);
			return (0);
		}
	}
	print_erro(retorno, cmds, geral);
	return (1);
}

void	finder_path(t_geral *geral)
{
	int		i;
	char	*tmp;
	char	*env;

	env = (char *)ctx_getenv(&geral->sh, "PATH");
	if (env == NULL)
		env = "Error";
	geral->gecmds.path = ft_split(env, ':');
	if (!geral->gecmds.path)
		return ;
	i = 0;
	while (geral->gecmds.path[i])
	{
		tmp = ft_strdup(geral->gecmds.path[i]);
		if (!tmp)
			return ;
		free(geral->gecmds.path[i]);
		geral->gecmds.path[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
}

char	**tokenlist_to_array(t_token *token_list)
{
	int		count;
	t_token	*tmp;
	char	**arr;

	count = 0;
	tmp = token_list;
	while (tmp && tmp->type != T_PIPE)
	{
		if (!(tmp->value && tmp->value[0] == '\0' && tmp->quote == NORMAL))
			count++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	tmp = token_list;
	count = 0;
	while (tmp && tmp->type != T_PIPE)
	{
		if (!(tmp->value && tmp->value[0] == '\0' && tmp->quote == NORMAL))
			arr[count++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return (arr[count] = NULL, arr);
}
