/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:24:33 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MAP_WALL_COLOR 0xE0E0E0
#define MAP_FLOOR_COLOR 0x303030
#define MAP_PLAYER_COLOR 0xFF2020
#define MAP_BORDER_COLOR 0x404040

/* Dessine un fond pour la minimap */
void	draw_minimap_background(t_game *game, int map_width, int map_height,
		int offset_x, int offset_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			if (offset_y + y < WIN_HEIGHT && offset_x + x < WIN_WIDTH)
				game->img_data[(offset_y + y) * (game->size_line / 4)
					+ (offset_x + x)] = 0x222222;
			x++;
		}
		y++;
	}
}

/* Dessine les éléments de la map (murs, sol) */
void	draw_map_elements(t_game *game, int size, int offset_x, int offset_y)
{
	int	map_y;
	int	map_x;
	int	pixel_x;
	int	pixel_y;
	int	color;
	int	y;
	int	x;

	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < (int)ft_strlen(game->map.grid[map_y]))
		{
			pixel_x = offset_x + map_x * size;
			pixel_y = offset_y + map_y * size;
			if (game->map.grid[map_y][map_x] == '1')
				color = MAP_WALL_COLOR;
			else if (game->map.grid[map_y][map_x] == '0'
				|| ft_strchr("NSEW", game->map.grid[map_y][map_x]))
				color = MAP_FLOOR_COLOR;
			else
			{
				map_x++;
				continue ;
			}
			y = 1;
			while (y < size - 1)
			{
				x = 1;
				while (x < size - 1)
				{
					if (pixel_y + y < WIN_HEIGHT && pixel_x + x < WIN_WIDTH)
						game->img_data[(pixel_y + y) * (game->size_line / 4)
							+ (pixel_x + x)] = color;
					x++;
				}
				y++;
			}
			map_x++;
		}
		map_y++;
	}
}