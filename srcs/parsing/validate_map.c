/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:12:10 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/04/30 16:18:03 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Vérifie si les bords du joueur/espace de jeu sont valides */
int	is_position_valid_and_closed(char **map, int x, int y, int height)
{
	int	start;
	int	end;

	if (y == 0 || y == height - 1)
		return (0);
	start = 0;
	end = ft_strlen(map[y]) - 1;
	while (map[y][start] == ' ')
		start++;
	while (end > 0 && map[y][end] == ' ')
		end--;
	if (x == start || x == end)
		return (0);
	if (y > 0 && (x >= (int)ft_strlen(map[y - 1]) || map[y - 1][x] == ' '))
		return (0);
	if (y < height - 1 && (x >= (int)ft_strlen(map[y + 1])
			|| map[y + 1][x] == ' '))
		return (0);
	if (x > 0 && map[y][x - 1] == ' ')
		return (0);
	if (x < (int)ft_strlen(map[y]) - 1 && map[y][x + 1] == ' ')
		return (0);
	return (1);
}

/* Vérifie si la map est fermée en contrôlant les espaces autour des zones jouables */
int	is_map_closed(char **map, int width, int height)
{
	char	c;
	int		x;
	int		y;

	(void)width;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (c == '0' || ft_strchr("PNSEWM", c))
			{
				if (!is_position_valid_and_closed(map, x, y, height))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/* Initialise l'orientation Nord */
void	init_player_north(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

/* Initialise l'orientation Sud, Est, Ouest */
void	init_player_direction(t_game *game, char dir)
{
	if (dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

/* Initialise la position et l'orientation du joueur selon la direction spécifiée */
void	init_player(t_game *game, int x, int y, char dir)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	if (dir == 'N')
		init_player_north(game);
	else
		init_player_direction(game, dir);
}