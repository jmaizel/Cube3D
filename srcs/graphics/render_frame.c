/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:00:00 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/14 10:42:06 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

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
}

void	render_frame(t_game *game)
{
	draw_floor_ceiling(game);
	complete_raycasting(game);
	render_monsters(game);
	draw_minimap(game);
	draw_weapon(game);
	draw_controls_menu(game);
}
