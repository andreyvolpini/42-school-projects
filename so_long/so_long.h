/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:12:17 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 17:12:17 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"

typedef struct s_images
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*exit_close;
	void	*exit_open;
	void	*coin;
}	t_images;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	int			collectibles;
	int			moves;
	t_images	img;
}	t_game;

void	free_map(char **map);
char	**read_map(char *file);
int		count_lines_in_file(char *file);
int		count_lines(char **map);

int		validate_elements(char **map);
int		validate_rectangle(char	**map);
int		validate_walls(char **map);
int		validate_path(char **map);

void	init_game(t_game *game, char **map);
void	load_images(t_game *game);
void	*chose_img(t_game *game, char tile);
void	render_map(t_game *game);

void	move_player(t_game *game, int x, int y);
void	exit_game(t_game *game);
int		handle_key(int keycode, t_game *game);

#endif
