/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginfranc <ginfranc@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:08:23 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/26 13:59:52 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_erro(int retorno, t_cmds *cmds, t_geral *geral)
{
	ft_putstr_fd(cmds->cmd[0], 2);
	geral->sh.g_status = 126;
	if (retorno == 3)
		ft_putstr_fd(": Is a directory\n", 2);
	else if (cmds->cmd[0][ft_strlen(cmds->cmd[0]) - 1] == '/'
		|| cmds->cmd[0][0] == '/'
		|| (cmds->cmd[0][0] == '.' && cmds->cmd[0][1] == '/'))
	{
		if (access(cmds->cmd[0], F_OK) == 0)
			ft_putstr_fd(": Permission denied\n", 2);
		else
		{
			geral->sh.g_status = 127;
			ft_putstr_fd(": No such file or directory\n", 2);
		}
	}
	else
	{
		geral->sh.g_status = 127;
		ft_putstr_fd(": command not found\n", 2);
	}
	cmds->path = ft_strdup("Error");
}

void	execution_and_free(t_geral *geral)
{
	set_fds(geral);
	execute_cmd(geral);
	if (geral->geopers.opers)
		close_pipered(geral);
	free_cmds(geral);
	geral->cmds = NULL;
}

void	execution_in_child(t_geral *g, int i)
{
	execve(g->cmds[i].path, g->cmds[i].cmd, g->vars.nenv);
	if (errno == ENOEXEC)
	{
		execve("/bin/sh", (char *[]){"sh",
			g->cmds[i].path, NULL}, g->vars.nenv);
	}
	perror("execve");
	exit(EXIT_FAILURE);
}

void	free_and_close(t_geral *g)
{
	cleanup_exit(g);
	exit(1);
}
