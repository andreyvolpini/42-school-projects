/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginfranc <ginfranc@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 08:40:01 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/26 10:44:45 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	counter_opers_utils(int *i, int *count, t_geral *geral)
{
	*i = 0;
	*count = 0;
	geral->geopers.n_opers = 0;
	if (!geral || !geral->tokens)
		return (1);
	geral->gecmds.n_cmds = 0;
	count_commands(geral, geral->tokens, 0);
	if (geral->gecmds.n_cmds > 0)
		geral->geopers.arr = malloc(sizeof(int) * geral->gecmds.n_cmds);
	else
		geral->geopers.arr = NULL;
	return (0);
}

void	counter_opers(t_geral *geral)
{
	t_token	*tmp;
	int		i;
	int		count;

	if (counter_opers_utils(&i, &count, geral) == 1)
		return ;
	tmp = geral->tokens;
	while (tmp)
	{
		if (tmp->type == T_IN || tmp->type == T_OUT
			|| tmp->type == T_APPEND || tmp->type == T_HEREDOC)
		{
			count++;
			geral->geopers.n_opers++;
		}
		if (tmp->type == T_PIPE)
		{
			geral->geopers.arr[i] = count;
			count = 0;
			i++;
		}
		tmp = tmp->next;
	}
	if (i < geral->gecmds.n_cmds)
		geral->geopers.arr[i] = count;
}

void	free_redirec(t_geral *geral)
{
	int	i;

	if (!geral)
		return ;
	i = 0;
	if (geral->geopers.opers)
	{
		while (i < geral->geopers.n_opers)
		{
			if (geral->geopers.opers[i].value)
			{
				free(geral->geopers.opers[i].value);
				geral->geopers.opers[i].value = NULL;
			}
			i++;
		}
		free(geral->geopers.opers);
		geral->geopers.opers = NULL;
	}
	if (geral->geopers.arr)
	{
		free(geral->geopers.arr);
		geral->geopers.arr = NULL;
	}
	geral->geopers.n_opers = 0;
}

int	open_fds_utils(t_geoper *geopers, int i, t_geral *geral)
{
	if (geopers->opers[i].type == T_OUT)
	{
		geopers->opers[i].fd = open(geopers->opers[i].value,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (geopers->opers[i].fd == -1)
			return (-1);
	}
	else if (geopers->opers[i].type == T_APPEND)
	{
		geopers->opers[i].fd = open(geopers->opers[i].value,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (geopers->opers[i].fd == -1)
			return (-1);
	}
	else if (geopers->opers[i].type == T_HEREDOC)
	{
		geopers->opers[i].fd = heredoc(geral, i);
		if (geopers->opers[i].fd == -1)
			return (-1);
	}
	return (0);
}

int	open_fds(t_geoper *geopers, t_geral *geral)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < geopers->n_opers)
	{
		if (geopers->opers[i].type == T_IN)
		{
			geopers->opers[i].fd = open(geopers->opers[i].value, O_RDONLY);
			if (geopers->opers[i].fd == -1)
			{
				geopers->opers[i].fd = -2;
				geral->geopers.n_erro = i;
				status = -1;
			}
		}
		else if (status == 0 && open_fds_utils(geopers, i, geral) == -1)
		{
			geopers->opers[i].fd = -2;
			geral->geopers.n_erro = i;
			return (-1);
		}
	}
	return (status);
}
