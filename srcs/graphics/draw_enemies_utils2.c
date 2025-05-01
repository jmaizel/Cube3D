/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:35:00 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/01 09:33:27 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Dessine une colonne de pixels d'un monstre avec transparence
 * 
 * @param game Structure principale du jeu
 * @param params Structure contenant les paramètres de dessin
 * @param monster_index Indice du monstre dans le tableau
 */
void	draw_monster_column(t_game *game, int stripe, int draw_start_y,
		int draw_end_y, t_sprite *sprite, int tex_x, int monster_index)
{
	int				y;
	int				color;
	t_draw_params	params;

	params.stripe = stripe;
	params.sprite = sprite;
	params.tex_x = tex_x;
	y = draw_start_y;
	while (y < draw_end_y)
	{
		params.y = y;
		color = get_monster_pixel(game, params, monster_index);
		draw_monster_pixel(game, params, color, monster_index);
		y++;
	}
}

/**
 * Calcule la position du sprite d'un monstre à l'écran
 * 
 * @param game Structure principale du jeu
 * @param order Indices des monstres triés par distance
 * @param i Indice dans le tableau order
 * @param sprite Structure pour stocker les informations du sprite
 * @return Structure contenant les informations calculées
 */
t_sprite	calc_sprite_pos(t_game *game, int *order, int i,
		t_sprite *sprite)
{
	double	inv_det;
	double	transform_x;
	double	transform_y;

	sprite->x = game->monsters[order[i]].x - game->player.x;
	sprite->y = game->monsters[order[i]].y - game->player.y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	transform_x = inv_det * (game->player.dir_y * sprite->x
			- game->player.dir_x * sprite->y);
	transform_y = inv_det * (-game->player.plane_y * sprite->x
			+ game->player.plane_x * sprite->y);
	sprite->width = abs((int)(WIN_HEIGHT / transform_y));
	sprite->height = sprite->width;
	sprite->screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x
				/ transform_y));
	sprite->transform_y = transform_y;
	return (*sprite);
}

/**
 * Calcule les limites de dessin du sprite
 * 
 * @param sprite Informations sur le sprite
 * @param limits Structure contenant les limites à calculer
 */
void	calc_sprite_draw_limits(t_sprite *sprite, int *draw_start_x,
		int *draw_end_x, int *draw_start_y, int *draw_end_y)
{
	*draw_start_y = -sprite->height / 2 + WIN_HEIGHT / 2;
	if (*draw_start_y < 0)
		*draw_start_y = 0;
	*draw_end_y = sprite->height / 2 + WIN_HEIGHT / 2;
	if (*draw_end_y >= WIN_HEIGHT)
		*draw_end_y = WIN_HEIGHT - 1;
	*draw_start_x = -sprite->width / 2 + sprite->screen_x;
	if (*draw_start_x < 0)
		*draw_start_x = 0;
	*draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (*draw_end_x >= WIN_WIDTH)
		*draw_end_x = WIN_WIDTH - 1;
}
