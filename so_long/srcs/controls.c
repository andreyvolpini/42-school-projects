/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:13:13 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 17:13:13 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void		exit_game(t_game *game);
void		move_player(t_game *game, int dx, int dy);
static void	handle_tile_action(t_game *game, char tile);
static void	update_player_position(t_game *game, int new_x, int new_y);

int	handle_key(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game(game);
	if (keycode == 'W' || keycode == 'w'
		|| keycode == 'Z' || keycode == 'z' || keycode == 65362)
		move_player(game, 0, -1);
	if (keycode == 'S' || keycode == 's' || keycode == 65364)
		move_player(game, 0, 1);
	if (keycode == 'A' || keycode == 'a'
		|| keycode == 'Q' || keycode == 'q' || keycode == 65361)
		move_player(game, -1, 0);
	if (keycode == 'D' || keycode == 'd' || keycode == 65363)
		move_player(game, 1, 0);
	return (0);
}

void	exit_game(t_game *game)
{
	if (game->img.wall)
		mlx_destroy_image(game->mlx, game->img.wall);
	if (game->img.floor)
		mlx_destroy_image(game->mlx, game->img.floor);
	if (game->img.player)
		mlx_destroy_image(game->mlx, game->img.player);
	if (game->img.exit_close)
		mlx_destroy_image(game->mlx, game->img.exit_close);
	if (game->img.exit_open)
		mlx_destroy_image(game->mlx, game->img.exit_open);
	if (game->img.coin)
		mlx_destroy_image(game->mlx, game->img.coin);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->map)
	{
		free_map(game->map);
		game->map = NULL;
	}
	exit(0);
}

void	move_player(t_game *game, int x, int y)
{
	int		new_x;
	int		new_y;
	char	tile;

	new_x = game->player_x + x;
	new_y = game->player_y + y;
	if (new_x < 0 || new_x >= game->width || new_y < 0 || new_y >= game->height)
		return ;
	tile = game->map[new_y][new_x];
	if (tile == '1')
		return ;
	if (tile == 'E' && game->collectibles > 0)
		return ;
	handle_tile_action(game, tile);
	update_player_position(game, new_x, new_y);
}

static void	handle_tile_action(t_game *game, char tile)
{
	if (tile == 'C')
		game->collectibles--;
	if (tile == 'E' && game->collectibles == 0)
	{
		game->moves++;
		ft_putstr_fd("Moves: ", 1);
		ft_putnbr_fd(game->moves, 1);
		ft_putstr_fd("\n-->You win!<--\n", 1);
		exit_game(game);
	}
}

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->moves, 1);
	write(1, "\n", 1);
	render_map(game);
}
