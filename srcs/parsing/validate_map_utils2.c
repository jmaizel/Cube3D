/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:32:14 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/02 18:53:04 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Initialise la direction du joueur (N)
 */
void	init_player_north(t_game *game, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

/**
 * Initialise la direction du joueur (S)
 */
void	init_player_south(t_game *game, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
}

/**
 * Initialise la direction du joueur (E)
 */
void	init_player_east(t_game *game, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

/**
 * Initialise la direction du joueur (W)
 */
void	init_player_west(t_game *game, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = -0.66;
}
