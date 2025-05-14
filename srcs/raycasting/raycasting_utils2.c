/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:18:00 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:57:23 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_wall_color(t_ray *ray)
{
	int	color;

	color = 0;
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			color = 0xFF0000;
		else
			color = 0x00FF00;
	}
	else
	{
		if (ray->dir_y > 0)
			color = 0x0000FF;
		else
			color = 0xFFFF00;
	}
	return (color);
}

static void	draw_pixel_if_valid(t_game *game, int x, int y, int color)
{
	if (y >= 0 && y < WIN_HEIGHT && x >= 0 && x < WIN_WIDTH)
		game->img_data[y * (game->size_line / 4) + x] = color;
}

void	safe_draw_textured_line(int x, t_ray *ray, t_game *game)
{
	int	color;
	int	y;

	color = get_wall_color(ray);
	if (ray->side == 1)
		color = (color >> 1) & 0x7F7F7F;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		draw_pixel_if_valid(game, x, y, color);
		y++;
	}
}
