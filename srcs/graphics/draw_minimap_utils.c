/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:05:30 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:40:50 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_line_params(t_line line, t_line *delta, t_line *sign)
{
	delta->x0 = abs(line.x1 - line.x0);
	delta->y0 = abs(line.y1 - line.y0);
	if (line.x0 < line.x1)
		sign->x0 = 1;
	else
		sign->x0 = -1;
	if (line.y0 < line.y1)
		sign->y0 = 1;
	else
		sign->y0 = -1;
}

static void	draw_point(t_game *game, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		game->img_data[y * (game->size_line / 4) + x] = color;
}

void	draw_line(t_game *game, t_line line, int color)
{
	t_line	delta;
	t_line	sign;
	int		err;
	int		e2;

	init_line_params(line, &delta, &sign);
	err = delta.x0 - delta.y0;
	draw_point(game, line.x0, line.y0, color);
	while (line.x0 != line.x1 || line.y0 != line.y1)
	{
		e2 = 2 * err;
		if (e2 > -delta.y0)
		{
			err -= delta.y0;
			line.x0 += sign.x0;
		}
		if (e2 < delta.x0)
		{
			err += delta.x0;
			line.y0 += sign.y0;
		}
		draw_point(game, line.x0, line.y0, color);
	}
}

void	draw_cell(t_game *game, t_minimap_pos pos, int color)
{
	int	i;
	int	j;

	i = 1;
	while (i < pos.cell_size - 1)
	{
		j = 1;
		while (j < pos.cell_size - 1)
		{
			if (pos.y + i < WIN_HEIGHT && pos.x + j < WIN_WIDTH)
				game->img_data[(pos.y + i) * (game->size_line / 4)
					+ (pos.x + j)] = color;
			j++;
		}
		i++;
	}
}
