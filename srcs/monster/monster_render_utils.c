/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_render_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:33:16 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:22:06 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Trie les monstres par distance pour le rendu */
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

/* Dessine une bande verticale du sprite du monstre */
void	render_monster_stripe(t_game *game, int stripe, t_sprite *sprite,
	int *draw_dims, int order_idx)
{
	int	tex_x;
	int	sprite_screen_x;

	sprite_screen_x = draw_dims[4];
	tex_x = (int)(256 * (stripe - (-sprite->width / 2 + sprite_screen_x))
			* game->monster_frames[0].width / sprite->width) / 256;
	if (draw_dims[5] > 0 && stripe > 0 && stripe < WIN_WIDTH
		&& draw_dims[5] < game->z_buffer[stripe])
	{
		draw_monster_column(game, stripe, draw_dims[0], draw_dims[1],
			sprite, tex_x, order_idx);
	}
}

/* Fonction principale pour rendre les monstres */
void	render_monsters(t_game *game)
{
	int			i;
	int			order[MAX_MONSTERS];
	double		distances[MAX_MONSTERS];
	t_sprite	sprite;
	int			draw_dims[6];
	int			stripe;
	int			sprite_screen_x;
	double		transform_y;

	if (game->monster_frame_count == 0)
		return ;
	sort_monsters(game, distances, order);
	i = 0;
	while (i < game->monster_count)
	{
		if (!game->monsters[order[i]].alive)
		{
			i++;
			continue ;
		}
		prepare_sprite_drawing(game, &sprite, order[i], &sprite_screen_x);
		calculate_sprite_dimensions(NULL, &sprite, sprite_screen_x, draw_dims);
		transform_y = distances[i];
		draw_dims[4] = sprite_screen_x;
		draw_dims[5] = (int)transform_y;
		stripe = draw_dims[2];
		while (stripe < draw_dims[3])
		{
			render_monster_stripe(game, stripe, &sprite, draw_dims, order[i]);
			stripe++;
		}
		i++;
	}
}