#include "../so_long.h"
#include "../libft/libft.h"

void	load_images(t_game *game)
{
	int	size;

	size = 32;
	game->img.wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &size, &size);
	game->img.floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &size, &size);
	game->img.player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &size, &size);
	game->img.exit_close = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_close.xpm", &size, &size);
	game->img.exit_open = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_open.xpm", &size, &size);
	game->img.coin = mlx_xpm_file_to_image(game->mlx,
			"textures/coin.xpm", &size, &size);
	if (!game->img.wall || !game->img.floor || !game->img.player
		|| !game->img.exit_close || !game->img.exit_open || !game->img.coin)
	{
		ft_putstr_fd("Error\nFailed to load .xpm images\n", 2);
		exit(1);
	}
}
