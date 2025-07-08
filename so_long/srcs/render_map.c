/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:21:33 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 17:21:33 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <stdio.h>

void	*chose_img(t_game *game, char tile);

void	render_map(t_game *game)
{
	int		x;
	int		y;
	void	*img;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			img = chose_img(game, game->map[y][x]);
			if (img)
				mlx_put_image_to_window(game->mlx, game->win, img,
					x * 32, y * 32);
		}
	}
}

void	*chose_img(t_game *game, char tile)
{
	if (tile == 'P')
		return (game->img.player);
	else if (tile == '1')
		return (game->img.wall);
	else if (tile == 'C')
		return (game->img.coin);
	else if (tile == 'E')
	{
		if (game->collectibles == 0)
			return (game->img.exit_open);
		else
			return (game->img.exit_close);
	}
	return (game->img.floor);
}
