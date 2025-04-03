/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/03 10:46:39 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_minimap(t_game *game)
{
	int map_x, map_y;
	int pixel_x, pixel_y;
	int size = 5;      // Taille de chaque case en pixels
	int offset_x = 20; // Position de la minimap dans la fenêtre
	int offset_y = 20;

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
				int y = 0;
				while (y < size)
				{
					int x = 0;
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
				int y = 0;
				while (y < size)
				{
					int x = 0;
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
	int player_pixel_x = offset_x + (int)(game->player.x) * size;
	int player_pixel_y = offset_y + (int)(game->player.y) * size;

	// Joueur - rouge
	int y = -1;
	while (y <= 1)
	{
		int x = -1;
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

void draw_gun(t_game *game)
{
    // Position du pistolet (centre bas de l'écran)
    int gun_x = WIN_WIDTH / 2;
    int gun_y = WIN_HEIGHT - 100;
    int size = 40;
    
    // Dessiner le canon (rectangle gris)
    int y = gun_y - 10;
    while (y < gun_y + 10)
    {
        int x = gun_x - size / 2;
        while (x < gun_x + size / 2)
        {
            if (y >= 0 && y < WIN_HEIGHT && x >= 0 && x < WIN_WIDTH)
                game->img_data[y * (game->size_line / 4) + x] = 0x444444;
            x++;
        }
        y++;
    }
    
    // Dessiner la poignée (rectangle gris foncé)
    y = gun_y + 10;
    while (y < gun_y + 40)
    {
        int x = gun_x - 15;
        while (x < gun_x + 5)
        {
            if (y >= 0 && y < WIN_HEIGHT && x >= 0 && x < WIN_WIDTH)
                game->img_data[y * (game->size_line / 4) + x] = 0x222222;
            x++;
        }
        y++;
    }
}