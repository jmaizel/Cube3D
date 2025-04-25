/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:04:32 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/25 13:26:07 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Vérifie si le joueur peut interagir avec une porte devant lui */
int	check_door_interaction(t_game *game)
{
	int	check_x;
	int	check_y;

	check_x = (int)(game->player.x + game->player.dir_x);
	check_y = (int)(game->player.y + game->player.dir_y);
	if (check_x >= 0 && check_y >= 0 && check_y < game->map.height
		&& check_x < (int)ft_strlen(game->map.grid[check_y])
		&& game->map.grid[check_y][check_x] == 'P')
	{
		return (1);
	}
	return (0);
}

/* Initialise toutes les portes de la map */
void	init_doors(t_game *game)
{
	int	x;
	int	y;

	game->door_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'P')
			{
				if (!game->door_path)
					return (exit_error("Error\nPorte trouvée mais pas de texture PO"),
						(void)0);
				game->door_positions[game->door_count][0] = x;
				game->door_positions[game->door_count][1] = y;
				game->door_state[game->door_count] = 0;
				game->door_count++;
			}
			x++;
		}
		y++;
	}
}