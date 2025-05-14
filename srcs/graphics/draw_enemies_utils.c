/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:15:30 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/14 10:39:40 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static int	apply_hit_effect(int color, int is_hit)
{
	int	red;

	if (!is_hit)
		return (color);
	red = (color >> 16) & 0xFF;
	red = fmin(255, red + 100);
	return ((red << 16) | (color & 0x00FFFF));
}

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
