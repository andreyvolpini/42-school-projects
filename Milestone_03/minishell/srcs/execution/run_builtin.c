/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:53:25 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:53:25 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_geral *geral, t_cmds *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (0);
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		return (builtin_echo(cmd));
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		return (builtin_pwd(geral));
	else if (!ft_strncmp(cmd->cmd[0], "env", 4))
		return (builtin_env(cmd, geral->sh.env));
	else if (!ft_strncmp(cmd->cmd[0], "exit", 5))
		return (builtin_exit(cmd, geral));
	else if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		return (builtin_cd(cmd->cmd, geral));
	else if (!ft_strncmp(cmd->cmd[0], "export", 7))
		return (builtin_export(geral, cmd));
	else if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		return (builtin_unset(geral, cmd));
	return (1);
}

int	is_builtin(t_cmds *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (0);
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		return (1);
	if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd->cmd[0], "env", 4))
		return (1);
	return (0);
}

int	is_parent_builtin(t_cmds *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (0);
	if (!ft_strncmp(cmd->cmd[0], "exit", 5))
		return (1);
	if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		return (1);
	if (!ft_strncmp(cmd->cmd[0], "export", 7))
		return (1);
	if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		return (1);
	return (0);
}

void	free_empty(t_geral *g, int i)
{
	const char	*name;

	name = NULL;
	if (!g || i < 0)
		return ;
	if (g->cmds[i].cmd && g->cmds[i].cmd[0])
		name = g->cmds[i].cmd[0];
	if (!name)
	{
		cleanup_exit(g);
		exit(0);
	}
	if (name[0] == '\0')
	{
		ft_putendl_fd("minishell: : command not found", 2);
		cleanup_exit(g);
		exit(127);
	}
	if (g->sh.g_status == 126)
	{
		cleanup_exit(g);
		exit(126);
	}
	cleanup_exit(g);
	exit(127);
}
