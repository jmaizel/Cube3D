/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:12:10 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/05/14 10:56:55 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_closed(char **map, int width, int height)
{
	char	c;
	int		x;
	int		y;

	(void)width;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (c == '0' || ft_strchr("PNSEWM", c))
			{
				if (!is_cell_enclosed(map, y, x, height))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

void	init_player(t_game *game, int x, int y, char dir)
{
	if (dir == 'N')
		init_player_north(game, x, y);
	else if (dir == 'S')
		init_player_south(game, x, y);
	else if (dir == 'E')
		init_player_east(game, x, y);
	else if (dir == 'W')
		init_player_west(game, x, y);
}

static int	check_map_characters(t_game *game, int *player_count)
{
	char		**map;
	int			y;
	int			x;
	t_map_check	check;

	map = game->map.grid;
	*player_count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			check.x = x;
			check.y = y;
			check.count = player_count;
			if (!process_map_char(game, map[y][x], &check))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	int	player_count;

	if (!check_map_characters(game, &player_count))
		return (0);
	if (player_count != 1)
		return (exit_error("Error\nAucun joueur trouvé"), 0);
	if (!is_map_closed(game->map.grid, game->map.width, game->map.height))
		return (exit_error("Error\nMap non fermée"), 0);
	return (1);
}
