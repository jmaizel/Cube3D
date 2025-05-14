/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:10:30 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:41:05 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_player_dot(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (i * i + j * j <= 4)
			{
				if (y + i >= 0 && y + i < WIN_HEIGHT && x + j >= 0
					&& x + j < WIN_WIDTH)
					game->img_data[(y + i) * (game->size_line / 4)
						+ (x + j)] = color;
			}
			j++;
		}
		i++;
	}
}

static void	draw_horizontal_borders(t_game *game, t_minimap_pos pos,
		t_minimap_size size, int color)
{
	int	i;
	int	border_size;

	border_size = 1;
	i = -border_size;
	while (i < size.width + border_size)
	{
		if (pos.y - border_size >= 0 && pos.x + i >= 0
			&& pos.y - border_size < WIN_HEIGHT && pos.x + i < WIN_WIDTH)
			game->img_data[(pos.y - border_size) * (game->size_line / 4)
				+ (pos.x + i)] = color;
		if (pos.y + size.height >= 0 && pos.x + i >= 0
			&& pos.y + size.height < WIN_HEIGHT && pos.x + i < WIN_WIDTH)
			game->img_data[(pos.y + size.height) * (game->size_line / 4)
				+ (pos.x + i)] = color;
		i++;
	}
}

static void	draw_vertical_borders(t_game *game, t_minimap_pos pos,
		t_minimap_size size, int color)
{
	int	i;
	int	border_size;

	border_size = 1;
	i = -border_size;
	while (i < size.height + border_size)
	{
		if (pos.y + i >= 0 && pos.x - border_size >= 0
			&& pos.y + i < WIN_HEIGHT && pos.x - border_size < WIN_WIDTH)
			game->img_data[(pos.y + i) * (game->size_line / 4)
				+ (pos.x - border_size)] = color;
		if (pos.y + i >= 0 && pos.x + size.width >= 0
			&& pos.y + i < WIN_HEIGHT && pos.x + size.width < WIN_WIDTH)
			game->img_data[(pos.y + i) * (game->size_line / 4)
				+ (pos.x + size.width)] = color;
		i++;
	}
}

void	draw_minimap_border(t_game *game, t_minimap_pos pos,
		t_minimap_size size)
{
	draw_horizontal_borders(game, pos, size, MAP_BORDER_COLOR);
	draw_vertical_borders(game, pos, size, MAP_BORDER_COLOR);
}

void	draw_minimap_background(t_game *game, t_minimap_pos pos,
		t_minimap_size size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.height)
	{
		x = 0;
		while (x < size.width)
		{
			if (pos.y + y < WIN_HEIGHT && pos.x + x < WIN_WIDTH)
				game->img_data[(pos.y + y) * (game->size_line / 4)
					+ (pos.x + x)] = MAP_BG_COLOR;
			x++;
		}
		y++;
	}
}
