/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/25 16:57:23 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define WEAPON_OFFSET_X 100
#define WEAPON_OFFSET_Y 30

/* Dessine l'arme en bas de l'écran */
void	draw_weapon(t_game *game)
{
	int x;
	int y;
	int draw_x;
	int draw_y;
	int color;
	int start_x;
	int start_y;

	if (!game->weapon_tex.data)
		return ;
	start_x = WIN_WIDTH / 2 - game->weapon_tex.width / 2 + 30;
	start_y = WIN_HEIGHT - game->weapon_tex.height + 10;
	y = 0;
	while (y < game->weapon_tex.height)
	{
		x = 0;
		while (x < game->weapon_tex.width)
		{
			color = game->weapon_tex.data[y * game->weapon_tex.width + x];
			if ((color & 0x00FFFFFF) != 0x000000)
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