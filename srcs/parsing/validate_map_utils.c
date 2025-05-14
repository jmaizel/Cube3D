/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:14 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:56:21 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_horizontal_bounds(char **map, int y, int x)
{
	int	start;
	int	end;
	int	line_len;

	line_len = ft_strlen(map[y]);
	start = 0;
	end = line_len - 1;
	while (map[y][start] == ' ')
		start++;
	while (end > 0 && map[y][end] == ' ')
		end--;
	if (x == start || x == end)
		return (0);
	if (x > 0 && map[y][x - 1] == ' ')
		return (0);
	if (x < line_len - 1 && map[y][x + 1] == ' ')
		return (0);
	return (1);
}

int	check_vertical_bounds(char **map, int y, int x)
{
	if (y == 0)
		return (0);
	if (x >= (int)ft_strlen(map[y - 1]) || map[y - 1][x] == ' ')
		return (0);
	if (y + 1 < 0 || !map[y + 1])
		return (0);
	if (x >= (int)ft_strlen(map[y + 1]) || map[y + 1][x] == ' ')
		return (0);
	return (1);
}

int	is_cell_enclosed(char **map, int y, int x, int height)
{
	if (y == 0 || y == height - 1)
		return (0);
	if (!check_horizontal_bounds(map, y, x))
		return (0);
	if (!check_vertical_bounds(map, y, x))
		return (0);
	return (1);
}

int	process_map_char(t_game *game, char c, t_map_check *check)
{
	if (!ft_strchr("01PNSEWMD ", c))
		return (exit_error("Error\nInvalid character in the map"), 0);
	if (ft_strchr("NSEW", c))
	{
		if ((*(check->count))++)
			return (exit_error("Error\nMore than one player found"), 0);
		init_player(game, check->x, check->y, c);
	}
	return (1);
}
