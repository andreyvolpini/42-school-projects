/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:13:00 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 17:13:00 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	is_validate_char(char c, int *p, int *e, int *c_count)
{
	if (c == 'P')
		(*p)++;
	else if (c == 'E')
		(*e)++;
	else if (c == 'C')
		(*c_count)++;
	else if (c != '0' && c != '1')
		return (0);
	return (1);
}

int	validate_elements(char **map)
{
	int	i;
	int	j;
	int	player;
	int	exit;
	int	coins;

	i = 0;
	player = 0;
	exit = 0;
	coins = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_validate_char(map[i][j], &player, &exit, &coins))
				return (ft_putstr_fd("Error\nInvalid char\n", 1), 0);
			j++;
		}
		i++;
	}
	if (player != 1 || exit != 1 || coins < 1)
		return (ft_putstr_fd("Error\nNeed 'P', 'E' and 'C'.\n", 1), 0);
	return (1);
}

int	validate_rectangle(char	**map)
{
	int	i;
	int	len;
	int	width;

	if (!map || !map[0])
		return (0);
	width = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len != width)
			return (ft_putstr_fd("Error\nNot rectangular.\n", 1), 0);
		i++;
	}
	return (1);
}

static int	check_top_bottom(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	validate_walls(char **map)
{
	int	len_x;
	int	len_y;
	int	y;

	len_x = ft_strlen(map[0]);
	len_y = count_lines(map);
	if (!check_top_bottom(map[0]) || !check_top_bottom(map[len_y - 1]))
		return (ft_putstr_fd("Error\nOpen at the top or bottom\n", 1), 0);
	y = 1;
	while (y < len_y -1)
	{
		if (map[y][0] != '1' || map[y][len_x - 1] != '1')
			return (ft_putstr_fd("Error\nOpen on the sides.\n", 1), 0);
		y++;
	}
	return (1);
}
