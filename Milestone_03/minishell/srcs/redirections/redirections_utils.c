/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:07:21 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/25 12:02:15 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*remove_token(t_geral *geral, t_token *node)
{
	t_token	*prev;
	t_token	*next;

	if (!node || !geral || !geral->tokens)
		return (NULL);
	if (geral->tokens == node)
	{
		next = node->next;
		if (node->value)
			free(node->value);
		free(node);
		geral->tokens = next;
		return (next);
	}
	prev = geral->tokens;
	while (prev && prev->next != node)
		prev = prev->next;
	if (!prev)
		return (NULL);
	next = node->next;
	prev->next = next;
	if (node->value)
		free(node->value);
	free(node);
	return (next);
}

int	finder_opers_utils(t_geral *geral, t_token *tmp, t_token **next, int i)
{
	if (!tmp || !next)
		return (-1);
	if (!tmp->next)
		return (*next = NULL, -1);
	geral->geopers.opers[i].fd = -1;
	geral->geopers.opers[i].type = tmp->type;
	if (!tmp->next->value)
	{
		*next = tmp->next;
		return (-1);
	}
	geral->geopers.opers[i].value = ft_strdup(tmp->next->value);
	if (!geral->geopers.opers[i].value)
		return (-1);
	*next = tmp->next->next;
	remove_token(geral, tmp->next);
	return (0);
}

int	finder_opers(t_geral *geral)
{
	int		i;
	t_token	*tmp;
	t_token	*next;

	i = -1;
	if (init_opers(geral) == 1)
		return (1);
	tmp = geral->tokens;
	while (tmp)
	{
		if (tmp->type == T_IN || tmp->type == T_OUT
			|| tmp->type == T_APPEND || tmp->type == T_HEREDOC)
		{
			next = tmp->next;
			if (finder_opers_utils(geral, tmp, &next, ++i) == -1)
				return (1);
			remove_token(geral, tmp);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
	if (open_fds(&geral->geopers, geral) != 0)
		return (1);
	return (0);
}
