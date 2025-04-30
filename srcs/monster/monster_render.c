/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:32:16 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:21:49 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Dessine un monstre avec transparence */
void	draw_monster_column(t_game *game, int stripe, int draw_start_y,
	int draw_end_y, t_sprite *sprite, int tex_x, int monster_index)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;
	int	frame;

	frame = game->monsters[monster_index].frame;
	if (frame >= game->monster_frame_count)
		frame = 0;
	y = draw_start_y;
	while (y < draw_end_y)
	{
		d = (y) * 256 - WIN_HEIGHT * 128 + sprite->height * 128;
		tex_y = ((d * game->monster_frames[frame].height) / sprite->height) / 256;
		if (tex_y >= 0 && tex_y < game->monster_frames[frame].height && tex_x >= 0
			&& tex_x < game->monster_frames[frame].width)
		{
			color = game->monster_frames[frame].data[game->monster_frames[frame].width
				* tex_y + tex_x];
			if ((color & 0x00FFFFFF) != 0x000000)
			{
				if (game->monsters[monster_index].hit_animation)
				{
					int red = (color >> 16) & 0xFF;
                    red = (red + 100 <= 255) ? red + 100 : 255;
                    color = (red << 16) | (color & 0x00FFFF);
				}
				game->img_data[y * (game->size_line / 4) + stripe] = color;
			}
		}
		y++;
	}
}

/* Calcule la position du sprite pour le rendu */
void	prepare_sprite_drawing(t_game *game, t_sprite *sprite, int order_idx,
	int *sprite_screen_x)
{
	double	inv_det;
	double	transform_x;
	double	transform_y;

	sprite->x = game->monsters[order_idx].x - game->player.x;
	sprite->y = game->monsters[order_idx].y - game->player.y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	transform_x = inv_det * (game->player.dir_y * sprite->x
			- game->player.dir_x * sprite->y);
	transform_y = inv_det * (-game->player.plane_y * sprite->x
			+ game->player.plane_x * sprite->y);
	*sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x
				/ transform_y));
	sprite->height = abs((int)(WIN_HEIGHT / transform_y));
	sprite->width = sprite->height;
}

/* Calcule les dimensions du sprite pour le rendu */
void	calculate_sprite_dimensions(t_ray *ray, t_sprite *sprite, int sprite_screen_x,
	int *draw_dims)
{
	int	draw_start_y;
	int	draw_end_y;
	int	draw_start_x;
	int	draw_end_x;

	draw_start_y = -sprite->height / 2 + WIN_HEIGHT / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite->height / 2 + WIN_HEIGHT / 2;
	if (draw_end_y >= WIN_HEIGHT)
		draw_end_y = WIN_HEIGHT - 1;
	draw_start_x = -sprite->width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite->width / 2 + sprite_screen_x;
	if (draw_end_x >= WIN_WIDTH)
		draw_end_x = WIN_WIDTH - 1;
	draw_dims[0] = draw_start_y;
	draw_dims[1] = draw_end_y;
	draw_dims[2] = draw_start_x;
	draw_dims[3] = draw_end_x;
	(void)ray;
}
