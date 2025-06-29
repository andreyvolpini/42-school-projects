#include "../so_long.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

int			count_lines_in_file(char *file);
int			count_lines(char **map);
void		free_map(char **map);
static int	fill_map_lines(char **map, int fd, int lines);

char	**read_map(char *file)
{
	int		fd;
	int		lines;
	char	**map;

	lines = count_lines_in_file(file);
	if (lines <= 0)
		return (ft_putstr_fd("Error\nEmpty file.\n", 2), NULL);
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (ft_putstr_fd("Error\nAlloc Map.\n", 2), NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (ft_putstr_fd("Error\nCan't open the file.\n", 2), NULL);
	}
	if (!fill_map_lines(map, fd, lines))
		return (ft_putstr_fd("Error\nFail to fill map.\n", 2), NULL);
	close(fd);
	return (map);
}

int	count_lines_in_file(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCan't open the file.\n", 2), -1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	count_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

static int	fill_map_lines(char **map, int fd, int lines)
{
	int		i;
	char	*newline;

	i = 0;
	while (i < lines)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
		{
			free_map(map);
			close(fd);
			return (0);
		}
		newline = ft_strchr(map[i], '\n');
		if (newline)
			*newline = '\0';
		i++;
	}
	map[i] = NULL;
	return (1);
}
