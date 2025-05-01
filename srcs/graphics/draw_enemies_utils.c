/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:15:30 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/01 09:48:17 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Initialise le tableau des distances et des indices
 * 
 * @param game Structure principale du jeu
 * @param distances Tableau des distances au carré
 * @param order Tableau des indices
 */
static void	init_monster_order(t_game *game, double *distances, int *order)
{
	int	i;

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
}

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

	init_monster_order(game, distances, order);
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
 * Applique l'effet de coup quand un monstre est touché
 * 
 * @param color Couleur originale
 * @param is_hit État d'animation de coup
 * @return Couleur modifiée
 */
static int	apply_hit_effect(int color, int is_hit)
{
	int	red;

	if (!is_hit)
		return (color);
	red = (color >> 16) & 0xFF;
	red = fmin(255, red + 100);
	return ((red << 16) | (color & 0x00FFFF));
}

/**
 * Dessine un pixel de monstre si la couleur n'est pas noire (transparente)
 * 
 * @param game Structure principale du jeu
 * @param params Structure contenant les paramètres de dessin
 * @param color Couleur du pixel
 * @param monster_index Indice du monstre
 */
void	draw_monster_pixel(t_game *game, t_draw_params params,
		int color, int monster_index)
{
	if ((color & 0x00FFFFFF) != 0x000000)
	{
		color = apply_hit_effect(color,
				game->monsters[monster_index].hit_animation);
		game->img_data[params.y * (game->size_line / 4)
			+ params.stripe] = color;
	}
}

/**
 * Récupère la couleur d'un pixel de la texture du monstre
 * 
 * @param game Structure principale du jeu
 * @param params Structure contenant les paramètres de dessin
 * @param monster_index Indice du monstre
 * @return Couleur du pixel ou 0 si hors limites
 */
int	get_monster_pixel(t_game *game, t_draw_params params,
		int monster_index)
{
	int	frame;
	int	tex_y;
	int	d;

	frame = game->monsters[monster_index].frame;
	if (frame >= game->monster_frame_count)
		frame = 0;
	d = (params.y) * 256 - WIN_HEIGHT * 128 + params.sprite->height * 128;
	tex_y = ((d * game->monster_frames[frame].height)
			/ params.sprite->height) / 256;
	if (tex_y >= 0 && tex_y < game->monster_frames[frame].height
		&& params.tex_x >= 0 && params.tex_x
		< game->monster_frames[frame].width)
	{
		return (game->monster_frames[frame].data[game->monster_frames
				[frame].width * tex_y + params.tex_x]);
	}
	return (0);
}
