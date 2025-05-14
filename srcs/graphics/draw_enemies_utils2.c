/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:35:00 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:39:54 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_monster_column(t_game *game, t_draw_params draw, int monster_index)
{
	int				y;
	int				color;
	t_draw_params	params;

	params.stripe = draw.stripe;
	params.sprite = draw.sprite;
	params.tex_x = draw.tex_x;
	y = draw.draw_start_y;
	while (y < draw.draw_end_y)
	{
		params.y = y;
		color = get_monster_pixel(game, params, monster_index);
		draw_monster_pixel(game, params, color, monster_index);
		y++;
	}
}

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

void	calc_sprite_draw_limits(t_sprite *sprite, t_draw_limits *limits)
{
	limits->draw_start_y = -sprite->height / 2 + WIN_HEIGHT / 2;
	if (limits->draw_start_y < 0)
		limits->draw_start_y = 0;
	limits->draw_end_y = sprite->height / 2 + WIN_HEIGHT / 2;
	if (limits->draw_end_y >= WIN_HEIGHT)
		limits->draw_end_y = WIN_HEIGHT - 1;
	limits->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	if (limits->draw_start_x < 0)
		limits->draw_start_x = 0;
	limits->draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (limits->draw_end_x >= WIN_WIDTH)
		limits->draw_end_x = WIN_WIDTH - 1;
}
