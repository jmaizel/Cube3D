/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/14 10:41:49 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_current_weapon_frame(t_game *game)
{
	int	current_frame;

	if (game->weapon_animating)
		current_frame = game->current_weapon_frame;
	else
		current_frame = 0;
	return (current_frame);
}

static void	init_weapon_draw_params(t_game *game, int current_frame,
		t_weapon_draw *params)
{
	params->start_x = WIN_WIDTH / 2
		- game->weapon_frames[current_frame].width / 2 + 30;
	params->start_y = WIN_HEIGHT
		- game->weapon_frames[current_frame].height + 10;
}

static void	draw_weapon_pixel(t_game *game, t_weapon_draw params)
{
	if (params.draw_x >= 0 && params.draw_x < WIN_WIDTH
		&& params.draw_y >= 0 && params.draw_y < WIN_HEIGHT)
		game->img_data[params.draw_y * (game->size_line / 4)
			+ params.draw_x] = params.color;
}

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
