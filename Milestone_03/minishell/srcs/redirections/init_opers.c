/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginfranc <ginfranc@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:59:13 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/25 14:54:44 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_opers(t_geral *geral)
{
	counter_opers(geral);
	if (geral->geopers.n_opers > 0)
	{
		geral->geopers.opers = malloc(sizeof(t_oper) * geral->geopers.n_opers);
		if (!geral->geopers.opers)
			return (1);
	}
	else
		geral->geopers.opers = NULL;
	return (0);
}
