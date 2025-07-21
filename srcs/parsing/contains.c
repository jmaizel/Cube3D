/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:30:50 by jmaizel           #+#    #+#             */
/*   Updated: 2025/06/02 11:49:21 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	contains_doors(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'D')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	contains_monsters(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'M')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map_texture_coherence(t_game *game)
{
	if (contains_doors(game) && game->door_tex.img == NULL)
	{
		exit_error("Error\nDoor found in map but no door texture (DR) defined");
		return (0);
	}
	if (contains_monsters(game) && game->monster_frame_count == 0)
	{
		exit_error("Error\nMonster found in map, no monster texture (MT0-MT3)");
		return (0);
	}
	return (1);
}

int	check_result(int result)
{
	if (result < 0 || result != 0)
		return (result);
	return (0);
}
