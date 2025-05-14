/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:31:16 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/14 10:40:14 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_monster(t_game *game, int x, int y)
{
	if (game->monster_frame_count == 0)
		ft_printf("Warning: Monstre trouvé mais pas de texture\n");
	game->monsters[game->monster_count].x = x + 0.5;
	game->monsters[game->monster_count].y = y + 0.5;
	game->monsters[game->monster_count].alive = 1;
	game->monsters[game->monster_count].frame = 0;
	game->monsters[game->monster_count].anim_time = 0.0;
	game->monsters[game->monster_count].anim_speed = 0.2;
	game->monsters[game->monster_count].health = 100;
	game->monsters[game->monster_count].max_health = 100;
	game->monsters[game->monster_count].hit_animation = 0;
	game->monsters[game->monster_count].hit_timer = 0.0;
	game->monster_count++;
	game->map.grid[y][x] = '0';
}

void	init_monsters(t_game *game)
{
	int	x;
	int	y;

	game->monster_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'M')
				init_monster(game, x, y);
			x++;
		}
		y++;
	}
}

static int	calc_tex_x(t_sprite *sprite, int stripe, int tex_width)
{
	return ((int)(256 * (stripe - (-sprite->width / 2 + sprite->screen_x))
		* tex_width / sprite->width) / 256);
}

void	process_monster_sprite(t_game *game, t_sprite *sprite,
		int monster_index)
{
	t_draw_limits	limits;
	t_draw_params	draw;
	int				stripe;
	int				tex_x;

	calc_sprite_draw_limits(sprite, &limits);
	draw.sprite = sprite;
	stripe = limits.draw_start_x;
	while (stripe < limits.draw_end_x)
	{
		tex_x = calc_tex_x(sprite, stripe, game->monster_frames[0].width);
		if (sprite->transform_y > 0 && stripe > 0 && stripe < WIN_WIDTH
			&& sprite->transform_y < game->z_buffer[stripe])
		{
			draw.stripe = stripe;
			draw.tex_x = tex_x;
			draw.draw_start_y = limits.draw_start_y;
			draw.draw_end_y = limits.draw_end_y;
			draw_monster_column(game, draw, monster_index);
		}
		stripe++;
	}
}
