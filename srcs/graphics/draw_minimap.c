/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/14 10:41:21 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_cell_color(t_game *game, int map_y, int map_x)
{
	char	cell_type;

	cell_type = game->map.grid[map_y][map_x];
	if (cell_type == '1')
		return (MAP_WALL_COLOR);
	else if (cell_type == '0' || ft_strchr("NSEWDMP", cell_type))
		return (MAP_FLOOR_COLOR);
	return (-1);
}

static void	draw_map_cells(t_game *game, t_minimap_pos pos)
{
	int				map_y;
	int				map_x;
	t_minimap_pos	cell_pos;
	int				color;

	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < (int)ft_strlen(game->map.grid[map_y]))
		{
			color = get_cell_color(game, map_y, map_x);
			if (color != -1)
			{
				cell_pos.x = pos.x + map_x * pos.cell_size;
				cell_pos.y = pos.y + map_y * pos.cell_size;
				cell_pos.cell_size = pos.cell_size;
				draw_cell(game, cell_pos, color);
			}
			map_x++;
		}
		map_y++;
	}
}

static void	draw_player(t_game *game, t_minimap_pos pos)
{
	t_line	line;
	int		player_x;
	int		player_y;

	player_x = pos.x + (int)(game->player.x * pos.cell_size);
	player_y = pos.y + (int)(game->player.y * pos.cell_size);
	draw_player_dot(game, player_x, player_y, MAP_PLAYER_COLOR);
	line.x0 = player_x;
	line.y0 = player_y;
	line.x1 = player_x + (int)(game->player.dir_x * pos.cell_size * 2);
	line.y1 = player_y + (int)(game->player.dir_y * pos.cell_size * 2);
	draw_line(game, line, MAP_PLAYER_COLOR);
}

static t_minimap_size	calculate_minimap_size(t_game *game,
		t_minimap_pos *pos)
{
	t_minimap_size	size;
	int				max_width;

	size.width = game->map.width * pos->cell_size;
	size.height = game->map.height * pos->cell_size;
	max_width = WIN_WIDTH / 4;
	if (size.width > max_width)
	{
		pos->cell_size = max_width / game->map.width;
		size.width = game->map.width * pos->cell_size;
		size.height = game->map.height * pos->cell_size;
	}
	return (size);
}

void	draw_minimap(t_game *game)
{
	t_minimap_pos	pos;
	t_minimap_size	size;

	pos.cell_size = 6;
	pos.x = 20;
	pos.y = 20;
	size = calculate_minimap_size(game, &pos);
	draw_minimap_background(game, pos, size);
	draw_map_cells(game, pos);
	draw_player(game, pos);
	draw_minimap_border(game, pos, size);
}
