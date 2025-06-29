#include "../so_long.h"
#include "../libft/libft.h"

static char	**dup_map(char **map);
static int	find_player(char **map, int *px, int *py);
static void	flood(char **map, int x, int y);
static int	is_valid(char **map);

int	validate_path(char **map)
{
	int		x;
	int		y;
	char	**copy;

	copy = dup_map(map);
	if (!copy)
		return (ft_putstr_fd("Error\nFailed to duplicate the map\n", 2), 0);
	x = 0;
	y = 0;
	if (!find_player(copy, &x, &y))
	{
		free_map(copy);
		return (ft_putstr_fd("Error\nPlayer not found on the map\n", 2), 0);
	}
	flood(copy, x, y);
	if (!is_valid(copy))
	{
		free_map(copy);
		return (ft_putstr_fd("Error\nNo valid path in the map\n", 2), 0);
	}
	free_map(copy);
	return (1);
}

static char	**dup_map(char **map)
{
	int		i;
	char	**copy;

	i = count_lines(map);
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (free_map(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	find_player(char **map, int *px, int *py)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				*px = x;
				*py = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static void	flood(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'E')
	{
		map[y][x] = 'F';
		return ;
	}
	map[y][x] = 'F';
	flood(map, x + 1, y);
	flood(map, x - 1, y);
	flood(map, x, y + 1);
	flood(map, x, y - 1);
}

static int	is_valid(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
