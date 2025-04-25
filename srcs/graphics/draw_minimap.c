/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/25 14:20:07 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Dessine un carré sur la minimap */
void	draw_minimap_square(t_game *game, int pixel_x, int pixel_y, int color)
{
	int	x;
	int	y;
	int	size;

	size = 5;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (pixel_y + y < WIN_HEIGHT && pixel_x + x < WIN_WIDTH)
				game->img_data[(pixel_y + y) * (game->size_line / 4) + (pixel_x
						+ x)] = color;
			x++;
		}
		y++;
	}
}

/* Dessine la position du joueur sur la minimap */
void	draw_minimap_player(t_game *game, int offset_x, int offset_y)
{
	int	x;
	int	y;
	int	player_pixel_x;
	int	player_pixel_y;
	int	size;

	size = 5;
	player_pixel_x = offset_x + (int)(game->player.x) * size;
	player_pixel_y = offset_y + (int)(game->player.y) * size;
	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			if (player_pixel_y + y < WIN_HEIGHT && player_pixel_x
				+ x < WIN_WIDTH)
				game->img_data[(player_pixel_y + y) * (game->size_line / 4)
					+ (player_pixel_x + x)] = 0xFF0000;
			x++;
		}
		y++;
	}
}

/* Dessine la minimap dans le coin supérieur gauche de l'écran */
void	draw_minimap(t_game *game)
{
	int offset_y;
	int map_x;
	int map_y;
	int pixel_x;
	int pixel_y;
	int size;
	int offset_x;

	size = 5;
	offset_x = 20;
	offset_y = 20;
	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < (int)ft_strlen(game->map.grid[map_y]))
		{
			pixel_x = offset_x + map_x * size;
			pixel_y = offset_y + map_y * size;
			if (game->map.grid[map_y][map_x] == '1')
				draw_minimap_square(game, pixel_x, pixel_y, 0xFFFFFF);
			else if (game->map.grid[map_y][map_x] == '0' || ft_strchr("NSEW",
					game->map.grid[map_y][map_x]))
				draw_minimap_square(game, pixel_x, pixel_y, 0x444444);
			map_x++;
		}
		map_y++;
	}
	draw_minimap_player(game, offset_x, offset_y);
}
