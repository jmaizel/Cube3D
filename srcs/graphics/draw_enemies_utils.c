/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:15:30 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/01 13:15:33 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Trie les monstres par distance pour le rendu
 * Utilise un tri à bulles pour trier du plus éloigné au plus proche
 * 
 * @param game Structure principale du jeu
 * @param distances Tableau des distances au carré entre joueur et monstres
 * @param order Tableau des indices triés par distance
 */
void	sort_monsters(t_game *game, double *distances, int *order)
{
	int		i;
	int		j;
	int		tmp;
	double	tmp_dist;

	i = 0;
	while (i < game->monster_count)
	{
		order[i] = i;
		distances[i] = ((game->player.x - game->monsters[i].x)
				* (game->player.x - game->monsters[i].x)
				+ (game->player.y - game->monsters[i].y)
				* (game->player.y - game->monsters[i].y));
		i++;
	}
	i = 0;
	while (i < game->monster_count - 1)
	{
		j = 0;
		while (j < game->monster_count - i - 1)
		{
			if (distances[j] < distances[j + 1])
			{
				tmp_dist = distances[j];
				distances[j] = distances[j + 1];
				distances[j + 1] = tmp_dist;
				tmp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/**
 * Dessine une colonne de pixels d'un monstre avec transparence
 * 
 * @param game Structure principale du jeu
 * @param stripe Coordonnée X de la colonne à dessiner
 * @param draw_start_y Coordonnée Y de début du dessin
 * @param draw_end_y Coordonnée Y de fin du dessin
 * @param sprite Informations sur le sprite à dessiner
 * @param tex_x Coordonnée X de la texture
 * @param monster_index Indice du monstre dans le tableau
 */
void	draw_monster_column(t_game *game, int stripe, int draw_start_y,
		int draw_end_y, t_sprite *sprite, int tex_x, int monster_index)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;
	int	frame;
	int	red;

	frame = game->monsters[monster_index].frame;
	if (frame >= game->monster_frame_count)
		frame = 0;
	y = draw_start_y;
	while (y < draw_end_y)
	{
		d = (y) * 256 - WIN_HEIGHT * 128 + sprite->height * 128;
		tex_y = ((d * game->monster_frames[frame].height) / sprite->height) / 256;
		if (tex_y >= 0 && tex_y < game->monster_frames[frame].height
			&& tex_x >= 0 && tex_x < game->monster_frames[frame].width)
		{
			color = game->monster_frames[frame].data[game->monster_frames
				[frame].width * tex_y + tex_x];
			if ((color & 0x00FFFFFF) != 0x000000)
			{
				if (game->monsters[monster_index].hit_animation)
				{
					red = (color >> 16) & 0xFF;
					red = fmin(255, red + 100);
					color = (red << 16) | (color & 0x00FFFF);
				}
				game->img_data[y * (game->size_line / 4) + stripe] = color;
			}
		}
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
 * @param draw_start_x Pointeur pour stocker X de début
 * @param draw_end_x Pointeur pour stocker X de fin
 * @param draw_start_y Pointeur pour stocker Y de début
 * @param draw_end_y Pointeur pour stocker Y de fin
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
