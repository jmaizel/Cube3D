/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:00:00 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/01 19:23:31 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:00:00 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/01 14:09:30 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Dessine le sol et le plafond de la scène 3D
 * 
 * @param game Structure principale du jeu
 */
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

/**
 * Dessine une frame complète avec sol, plafond, murs, minimap et arme
 * 
 * @param game Structure principale du jeu
 */
void	render_frame(t_game *game)
{
	draw_floor_ceiling(game);
	complete_raycasting(game);
	render_monsters(game);
	draw_minimap(game);
	draw_weapon(game);
	draw_controls_menu(game);
}
