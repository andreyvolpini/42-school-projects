#include "../so_long.h"
#include "../libft/libft.h"
#include <fcntl.h>

int	is_valid_ber(char *filename);
int	close_game(t_game *game);
int	check_args(int ac, char **av);

int	main(int ac, char **av)
{
	char		**map;
	t_game		game;

	if (!check_args(ac, av))
		return (1);
	map = read_map(av[1]);
	if (!map)
		return (1);
	if (!validate_elements(map) || !validate_rectangle(map)
		|| !validate_walls(map) || !validate_path(map))
		return (free_map(map), 1);
	init_game(&game, map);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.width * 32,
			game.height * 32, "so_long");
	load_images(&game);
	if (!game.img.player || !game.img.wall || !game.img.coin
		|| !game.img.exit_close || !game.img.exit_open || !game.img.floor)
		return (ft_putstr_fd("Error\nOne or more textures are NULL\n", 2), 1);
	render_map(&game);
	mlx_key_hook(game.win, handle_key, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}

int	check_args(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (ft_putstr_fd("Error\nMissing: mapa.ber\n", 2), 1);
	if (!is_valid_ber(av[1]))
		return (ft_putstr_fd("Error\nMap should be .ber\n", 2), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCan't read file\n", 2), 1);
	close(fd);
	return (1);
}

int	is_valid_ber(char *filename)
{
	int	len;
	int	cmp;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	cmp = ft_strncmp(filename + len - 4, ".ber", 4);
	if (!cmp)
		return (1);
	return (0);
}

int	close_game(t_game *game)
{
	exit_game(game);
	return (0);
}
