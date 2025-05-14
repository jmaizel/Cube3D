/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:50:20 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:42:20 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	apply_side_shading(int color)
{
	return ((color >> 1) & 0x7F7F7F);
}

int	change_door_color(int color)
{
	int	red;
	int	green;
	int	blue;
	int	new_green;
	int	new_red;

	red = ((color >> 16) & 0xFF);
	green = ((color >> 8) & 0xFF);
	blue = (color & 0xFF);
	if ((red > green && red > blue) || (red > 60 && red > green * 1.5
			&& red > blue * 1.5))
	{
		new_green = red * 1.2;
		if (new_green > 255)
			new_green = 255;
		new_red = green * 0.7;
		return ((new_red << 16) | (new_green << 8) | blue);
	}
	return (color);
}

void	free_texture_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->weapon_frame_count)
	{
		if (game->weapon_paths[i])
		{
			free(game->weapon_paths[i]);
			game->weapon_paths[i] = NULL;
		}
		i++;
	}
	i = 0;
	while (i < game->monster_frame_count)
	{
		if (game->monster_paths[i])
		{
			free(game->monster_paths[i]);
			game->monster_paths[i] = NULL;
		}
		i++;
	}
}
