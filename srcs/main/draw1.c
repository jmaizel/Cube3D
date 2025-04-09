/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/09 16:21:53 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_minimap(t_game *game)
{
	int	offset_y;
	int	y;
	int	x;
	int	player_pixel_x;
	int	player_pixel_y;

	int map_x, map_y;
	int pixel_x, pixel_y;
	int size = 5;      // Taille de chaque case en pixels
	int offset_x = 20; // Position de la minimap dans la fenêtre
	offset_y = 20;
	// Dessiner le fond de la minimap
	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < (int)ft_strlen(game->map.grid[map_y]))
		{
			// Calculer les coordonnées du pixel
			pixel_x = offset_x + map_x * size;
			pixel_y = offset_y + map_y * size;
			// Dessiner le carré selon le type de case
			if (game->map.grid[map_y][map_x] == '1')
			{
				// Mur - blanc
				y = 0;
				while (y < size)
				{
					x = 0;
					while (x < size)
					{
						if (pixel_y + y < WIN_HEIGHT && pixel_x + x < WIN_WIDTH)
							game->img_data[(pixel_y + y) * (game->size_line / 4)
								+ (pixel_x + x)] = 0xFFFFFF;
						x++;
					}
					y++;
				}
			}
			else if (game->map.grid[map_y][map_x] == '0' || ft_strchr("NSEW",
					game->map.grid[map_y][map_x]))
			{
				// Sol - gris
				y = 0;
				while (y < size)
				{
					x = 0;
					while (x < size)
					{
						if (pixel_y + y < WIN_HEIGHT && pixel_x + x < WIN_WIDTH)
							game->img_data[(pixel_y + y) * (game->size_line / 4)
								+ (pixel_x + x)] = 0x444444;
						x++;
					}
					y++;
				}
			}
			map_x++;
		}
		map_y++;
	}
	// Dessiner la position du joueur
	player_pixel_x = offset_x + (int)(game->player.x) * size;
	player_pixel_y = offset_y + (int)(game->player.y) * size;
	// Joueur - rouge
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

#define WEAPON_OFFSET_X 100
#define WEAPON_OFFSET_Y 30

void	draw_weapon(t_game *game)
{
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;
	int	color;
	int	start_x;
	int	start_y;

	start_x = WIN_WIDTH / 2 - game->weapon_tex.width / 2 + 30;
	start_y = WIN_HEIGHT - game->weapon_tex.height + 10;
	y = 0;
	while (y < game->weapon_tex.height)
	{
		x = 0;
		while (x < game->weapon_tex.width)
		{
			color = game->weapon_tex.data[y * game->weapon_tex.width + x];
			if ((color & 0x00FFFFFF) != 0x000000) // ignore le noir
			{
				draw_x = start_x + x;
				draw_y = start_y + y;
				if (draw_x >= 0 && draw_x < WIN_WIDTH && draw_y >= 0
					&& draw_y < WIN_HEIGHT)
					game->img_data[draw_y * (game->size_line / 4)
						+ draw_x] = color;
			}
			x++;
		}
		y++;
	}
}
