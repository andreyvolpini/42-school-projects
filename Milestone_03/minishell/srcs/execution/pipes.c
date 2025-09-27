/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginfranc <ginfranc@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:00:34 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/25 14:53:01 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fds_utils(t_geral *geral, int j, int i)
{
	if (geral->geopers.opers[j].type == T_IN
		|| geral->geopers.opers[j].type == T_HEREDOC)
	{
		if (geral->cmds[i].fd_in != -1)
			close(geral->cmds[i].fd_in);
		if (geral->cmds[i].fd_in == -2)
			return ;
		geral->cmds[i].fd_in = geral->geopers.opers[j].fd;
	}
	else if (geral->geopers.opers[j].type == T_OUT
		|| geral->geopers.opers[j].type == T_APPEND)
	{
		if (geral->cmds[i].fd_out != -1)
			close(geral->cmds[i].fd_out);
		if (geral->cmds[i].fd_out == -2)
			return ;
		geral->cmds[i].fd_out = geral->geopers.opers[j].fd;
	}
}

void	close_pipered(t_geral *geral)
{
	int	i;

	i = 0;
	while (i < geral->gecmds.n_cmds)
	{
		if (geral->cmds[i].fd_in != -1 && geral->cmds[i].fd_in != -2)
			close(geral->cmds[i].fd_in);
		geral->cmds[i].fd_in = -1;
		if (geral->cmds[i].fd_out != -1 && geral->cmds[i].fd_out != -2)
			close(geral->cmds[i].fd_out);
		geral->cmds[i].fd_out = -1;
		i++;
	}
	if (geral->gecmds.n_cmds == 0)
	{
		if (geral->geopers.opers[0].fd != -1
			&& geral->geopers.opers[0].fd != -2)
		{
			close(geral->geopers.opers[0].fd);
			geral->geopers.opers[0].fd = -1;
		}
	}
}

void	close_all_pipes(t_geral *geral, int pipefd[2][2], int i)
{
	int	a;
	int	b;

	a = -1;
	while (++a < 2)
	{
		b = -1;
		while (++b < 2)
		{
			if (pipefd[a][b] != -1)
			{
				close(pipefd[a][b]);
				pipefd[a][b] = -1;
			}
		}
	}
	if (i >= 0)
	{
		if (geral->cmds[i].fd_in != -1 && geral->cmds[i].fd_in != -2)
			close(geral->cmds[i].fd_in);
		if (geral->cmds[i].fd_out != -1 && geral->cmds[i].fd_out != -2)
			close(geral->cmds[i].fd_out);
	}
}

void	init_pipes(int pipefd[2][2])
{
	int		a;
	int		b;

	a = 0;
	while (a < 2)
	{
		b = 0;
		while (b < 2)
		{
			pipefd[a][b] = -1;
			b++;
		}
		a++;
	}
}

void	close_pipes(int pipefd[2][2], int i)
{
	if (i > 0)
	{
		if (pipefd[(i + 1) % 2][0] != -1)
		{
			close(pipefd[(i + 1) % 2][0]);
			pipefd[(i + 1) % 2][0] = -1;
		}
		if (pipefd[(i + 1) % 2][1] != -1)
		{
			close(pipefd[(i + 1) % 2][1]);
			pipefd[(i + 1) % 2][1] = -1;
		}
	}
}
