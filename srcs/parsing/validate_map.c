/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:12:10 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/04/25 16:50:30 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Vérifie si la map est fermée en contrôlant les espaces autour des zones jouables */
int	is_map_closed(char **map, int width, int height)
{
	char	c;
	int		x;
	int		y;
	int		start;
	int		end;

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
				if (y > 0 && (x >= (int)ft_strlen(map[y - 1]) || map[y
						- 1][x] == ' '))
					return (0);
				if (y < height - 1 && (x >= (int)ft_strlen(map[y + 1]) || map[y
						+ 1][x] == ' '))
					return (0);
				if (x > 0 && map[y][x - 1] == ' ')
					return (0);
				if (x < (int)ft_strlen(map[y]) - 1 && map[y][x + 1] == ' ')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/* Initialise la position et l'orientation du joueur selon la direction spécifiée */
void	init_player(t_game *game, int x, int y, char dir)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	if (dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (dir == 'S')
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

/* Valide la map en vérifiant les caractères,
	le nombre de joueurs et si elle est fermée */
int	validate_map(t_game *game)
{
	int player_count;
	char **map;
	char c;
	int y;
	int x;

	player_count = 0;
	map = game->map.grid;

	y = 0;
	while (map[y])
	{
		y++;
	}

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];

			if (!ft_strchr("01PNSEWM ", c))
				return (exit_error("Error\nCaractère invalide dans la map"), 0);
			if (ft_strchr("NSEW", c))
			{
				if (player_count++)
					return (exit_error("Error\nPlus d'un joueur trouvé"), 0);
				init_player(game, x, y, c);
			}
			x++;
		}
		y++;
	}

	if (player_count != 1)
		return (exit_error("Error\nAucun joueur trouvé"), 0);
	if (!is_map_closed(game->map.grid, game->map.width, game->map.height))
		return (exit_error("Error\nMap non fermée"), 0);
	return (1);
}