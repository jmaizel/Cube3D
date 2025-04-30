/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 17:36:45 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Dessine un fond uniforme pour la minimap
 * 
 * @param game Structure principale du jeu
 * @param offset_x Position X de la minimap
 * @param offset_y Position Y de la minimap
 * @param map_width Largeur de la minimap en pixels
 * @param map_height Hauteur de la minimap en pixels
 */
static void	draw_minimap_background(t_game *game, int offset_x, int offset_y,
		int map_width, int map_height)
{
	int	x;
	int	y;

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

/**
 * Dessine les cases (murs et sol) de la minimap
 * 
 * @param game Structure principale du jeu
 * @param size Taille en pixels de chaque case
 * @param offset_x Position X de la minimap
 * @param offset_y Position Y de la minimap
 */
static void	draw_minimap_grid(t_game *game, int size, int offset_x, int offset_y)
{
	int	map_y;
	int	map_x;
	int	pixel_x;
	int	pixel_y;
	int	color;
	int	x;
	int	y;

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

/**
 * Dessine la position et la direction du joueur sur la minimap
 * 
 * @param game Structure principale du jeu
 * @param size Taille en pixels de chaque case
 * @param offset_x Position X de la minimap
 * @param offset_y Position Y de la minimap
 */
static void	draw_player_on_minimap(t_game *game, int size, int offset_x,
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
				if (player_pixel_y + y < WIN_HEIGHT && player_pixel_x + x < WIN_WIDTH
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

/**
 * Dessine la minimap du jeu dans le coin supérieur gauche de l'écran
 * 
 * @param game Structure principale du jeu
 */
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
	draw_minimap_background(game, offset_x, offset_y, map_width, map_height);
	draw_minimap_grid(game, size, offset_x, offset_y);
	draw_player_on_minimap(game, size, offset_x, offset_y);
	draw_minimap_border(game, offset_x, offset_y, map_width, map_height);
}