/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:44:32 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/26 13:53:33 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fds(t_geral *geral)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = 0;
	while (++i < geral->gecmds.n_cmds)
	{
		count = 0;
		while (count < geral->geopers.arr[i])
		{
			set_fds_utils(geral, j, i);
			j++;
			count++;
		}
	}
}

void	execute_cmd(t_geral *geral)
{
	if (geral->gecmds.n_cmds == 1)
	{
		if (is_parent_builtin(&geral->cmds[0]))
			geral->sh.g_status = run_builtin(geral, &geral->cmds[0]);
		else
			execute_all(geral, -1);
	}
	else
		execute_all(geral, -1);
}

void	free_cmds(t_geral *geral)
{
	int	i;

	if (!geral || !geral->cmds)
		return ;
	i = 0;
	while (i < geral->gecmds.n_cmds)
	{
		free_arr(geral->cmds[i].cmd);
		if (geral->cmds[i].path)
		{
			free(geral->cmds[i].path);
			geral->cmds[i].path = NULL;
		}
		i++;
	}
	if (geral->gecmds.path)
	{
		free_arr(geral->gecmds.path);
		geral->gecmds.path = NULL;
	}
	free(geral->cmds);
	geral->cmds = NULL;
	free_redirec(geral);
}

void	create_cmds_utils(t_geral *geral, int i)
{
	geral->cmds[i].fd_in = -1;
	geral->cmds[i].fd_out = -1;
	geral->cmds[i].path = NULL;
	geral->cmds[i].error = 0;
	if (!is_builtin(&geral->cmds[i]) && !is_parent_builtin(&geral->cmds[i]))
		if (cmds_test(geral, &geral->cmds[i]) == 1)
			geral->cmds[i].error = -1;
}

void	create_cmds(t_geral *geral, int i)
{
	t_token	*tmp;
	t_token	*cmd_start;

	geral->gecmds.n_cmds = 0;
	count_commands(geral, geral->tokens, 1);
	geral->cmds = malloc(sizeof(t_cmds) * (geral->gecmds.n_cmds + 1));
	tmp = geral->tokens;
	while (++i < geral->gecmds.n_cmds)
	{
		if (tmp && tmp->value == NULL)
			tmp = tmp->next;
		cmd_start = tmp;
		while (tmp && tmp->type != T_PIPE)
			tmp = tmp->next;
		geral->cmds[i].cmd = tokenlist_to_array(cmd_start);
		create_cmds_utils(geral, i);
		if (tmp && tmp->type == T_PIPE)
			tmp = tmp->next;
	}
	execution_and_free(geral);
}
