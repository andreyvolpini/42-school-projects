/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:13:16 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 17:13:16 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	scan_map(t_game *game, char **map);

void	init_game(t_game *game, char **map)
{
	if (!map || !map[0])
	{
		ft_putstr_fd("Error\nInvalid map at startup\n", 2);
		exit (1);
	}
	game->map = map;
	game->height = count_lines(map);
	game->width = ft_strlen(map[0]);
	game->moves = 0;
	game->collectibles = 0;
	game->player_x = -1;
	game->player_y = -1;
	if (!scan_map(game, map))
		exit(1);
}

static int	scan_map(t_game *game, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
			}
			else if (map[y][x] == 'C')
				game->collectibles++;
			x++;
		}
		y++;
	}
	if (game->player_x == -1 || game->player_y == -1)
		return (ft_putstr_fd("Error\nPlayer not found on the map\n", 2), 0);
	return (1);
}
