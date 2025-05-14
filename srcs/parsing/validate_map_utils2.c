/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:32:14 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:56:35 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player_north(t_game *game, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

void	init_player_south(t_game *game, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
}

void	init_player_east(t_game *game, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

void	init_player_west(t_game *game, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = -0.66;
}
