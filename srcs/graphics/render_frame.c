/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:00:00 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/28 17:37:34 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Dessine une frame complète avec sol, plafond, murs, minimap et arme */
void	render_frame(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				game->img_data[y * (game->size_line / 4)
					+ x] = game->ceiling_color;
			else
				game->img_data[y * (game->size_line / 4)
					+ x] = game->floor_color;
			x++;
		}
		y++;
	}
	complete_raycasting(game);
    render_monsters(game);
	draw_minimap(game);
	draw_weapon(game);
	draw_controls_menu(game);
}