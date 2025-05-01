/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/01 19:22:12 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Détermine la frame actuelle pour l'animation de l'arme
 * 
 * @param game Structure principale du jeu
 * @return Indice de la frame actuelle
 */
static int	get_current_weapon_frame(t_game *game)
{
	int	current_frame;

	if (game->weapon_animating)
		current_frame = game->current_weapon_frame;
	else
		current_frame = 0;
	return (current_frame);
}

/**
 * Initialise les positions pour le dessin de l'arme
 * 
 * @param game Structure principale du jeu
 * @param current_frame Indice de la frame actuelle
 * @param params Structure à remplir avec les paramètres
 */
static void	init_weapon_draw_params(t_game *game, int current_frame,
		t_weapon_draw *params)
{
	params->start_x = WIN_WIDTH / 2
		- game->weapon_frames[current_frame].width / 2 + 30;
	params->start_y = WIN_HEIGHT
		- game->weapon_frames[current_frame].height + 10;
}

/**
 * Dessine un pixel de l'arme à la position spécifiée
 * 
 * @param game Structure principale du jeu
 * @param params Paramètres de dessin
 */
static void	draw_weapon_pixel(t_game *game, t_weapon_draw params)
{
	if (params.draw_x >= 0 && params.draw_x < WIN_WIDTH
		&& params.draw_y >= 0 && params.draw_y < WIN_HEIGHT)
		game->img_data[params.draw_y * (game->size_line / 4)
			+ params.draw_x] = params.color;
}

/**
 * Dessine l'arme du joueur en bas de l'écran avec animation
 * Utilise la frame actuelle de l'animation déterminée par weapon_animating
 *
 * @param game Structure principale du jeu
 */
void	draw_weapon(t_game *game)
{
	t_weapon_draw	params;
	int				current_frame;

	current_frame = get_current_weapon_frame(game);
	if (!game->weapon_frames[current_frame].data)
		return ;
	init_weapon_draw_params(game, current_frame, &params);
	params.y = 0;
	while (params.y < game->weapon_frames[current_frame].height)
	{
		params.x = 0;
		while (params.x < game->weapon_frames[current_frame].width)
		{
			params.color = game->weapon_frames[current_frame].data[params.y
				* game->weapon_frames[current_frame].width + params.x];
			if ((params.color & 0x00FFFFFF) != 0x000000)
			{
				params.draw_x = params.start_x + params.x;
				params.draw_y = params.start_y + params.y;
				draw_weapon_pixel(game, params);
			}
			params.x++;
		}
		params.y++;
	}
}
