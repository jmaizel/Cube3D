/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:11:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 17:15:42 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MAP_WALL_COLOR 0xE0E0E0
#define MAP_FLOOR_COLOR 0x303030
#define MAP_PLAYER_COLOR 0xFF2020
#define MAP_BORDER_COLOR 0x404040

/* Dessine la position du joueur sur la minimap */
void	draw_player_on_minimap(t_game *game, int size, int offset_x,
	int offset_y)
{
	int	player_pixel_x;
	int	player_pixel_y;
	int	player_radius;
	int	dir_length;
	int	dir_end_x;
	int	dir_end_y;
	int	x;
	int	y;

	player_pixel_x = offset_x + (int)(game->player.x * size);
	player_pixel_y = offset_y + (int)(game->player.y * size);
	player_radius = 3;
	y = -player_radius;
	while (y <= player_radius)
	{
		x = -player_radius;
		while (x <= player_radius)
		{
			if (x * x + y * y <= player_radius * player_radius)
			{
				if (player_pixel_y + y < WIN_HEIGHT
					&& player_pixel_x + x < WIN_WIDTH
					&& player_pixel_y + y >= 0 && player_pixel_x + x >= 0)
					game->img_data[(player_pixel_y + y) * (game->size_line / 4)
						+ (player_pixel_x + x)] = MAP_PLAYER_COLOR;
			}
			x++;
		}
		y++;
	}
	dir_length = size * 2;
	dir_end_x = player_pixel_x + (int)(game->player.dir_x * dir_length);
	dir_end_y = player_pixel_y + (int)(game->player.dir_y * dir_length);
	draw_line(game, player_pixel_x, player_pixel_y, dir_end_x, dir_end_y,
		MAP_PLAYER_COLOR);
}

/* Dessine une ligne (algorithme de Bresenham) */
void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		if (x0 >= 0 && y0 >= 0 && x0 < WIN_WIDTH && y0 < WIN_HEIGHT)
			game->img_data[y0 * (game->size_line / 4) + x0] = color;
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

/* Dessine un cadre autour de la minimap */
void	draw_minimap_border(t_game *game, int x, int y, int width, int height)
{
	int	border_size;
	int	border_color;
	int	i;
	int	j;

	border_size = 2;
	border_color = MAP_BORDER_COLOR;
	i = -border_size;
	while (i < width + border_size)
	{
		j = -border_size;
		while (j < 0)
		{
			if (y + j >= 0 && x + i >= 0 && y + j < WIN_HEIGHT
				&& x + i < WIN_WIDTH)
				game->img_data[(y + j) * (game->size_line / 4)
					+ (x + i)] = border_color;
			j++;
		}
		j = height;
		while (j < height + border_size)
		{
			if (y + j >= 0 && x + i >= 0 && y + j < WIN_HEIGHT
				&& x + i < WIN_WIDTH)
				game->img_data[(y + j) * (game->size_line / 4)
					+ (x + i)] = border_color;
			j++;
		}
		i++;
	}
	i = -border_size;
	while (i < height + border_size)
	{
		j = -border_size;
		while (j < 0)
		{
			if (y + i >= 0 && x + j >= 0 && y + i < WIN_HEIGHT
				&& x + j < WIN_WIDTH)
				game->img_data[(y + i) * (game->size_line / 4)
					+ (x + j)] = border_color;
			j++;
		}
		j = width;
		while (j < width + border_size)
		{
			if (y + i >= 0 && x + j >= 0 && y + i < WIN_HEIGHT
				&& x + j < WIN_WIDTH)
				game->img_data[(y + i) * (game->size_line / 4)
					+ (x + j)] = border_color;
			j++;
		}
		i++;
	}
}

/* Fonction principale de la minimap */
void	draw_minimap(t_game *game)
{
	int	size;
	int	offset_x;
	int	offset_y;
	int	map_width;
	int	map_height;
	int	max_map_size;

	size = 7;
	offset_x = 30;
	offset_y = 30;
	map_width = game->map.width * size;
	map_height = game->map.height * size;
	max_map_size = 200;
	if (map_width > max_map_size)
	{
		size = max_map_size / game->map.width;
		map_width = game->map.width * size;
		map_height = game->map.height * size;
	}
	draw_minimap_background(game, map_width, map_height, offset_x, offset_y);
	draw_map_elements(game, size, offset_x, offset_y);
	draw_player_on_minimap(game, size, offset_x, offset_y);
	draw_minimap_border(game, offset_x, offset_y, map_width, map_height);
}