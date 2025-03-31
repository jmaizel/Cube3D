/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacobmaizel <jacobmaizel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:12:10 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/03/31 13:16:16 by jacobmaizel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
dans cette fonction on regarde pour chaque 0 N/S/E/W si ce n est pa au bord
donc on regarde si il n y a pas un espace ou au bord ca veut dire que la map n est pas fermee
*/
int	is_map_closed(char **map, int width, int height)
{
	char	c;

	int x, y;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (c == '0' || ft_strchr("NSEW", c))
			{
				if (y == 0 || x == 0 || y == height - 1
					|| x >= (int)ft_strlen(map[y]) - 1)
					return (0);
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x
					- 1] == ' ' || map[y][x + 1] == ' ' || map[y - 1][x] == '\0'
					|| map[y + 1][x] == '\0')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/*
fonction qui va regarder si la map est valide maintenant, on regarde :
1. si les caracteres sont valides
2. si il y a bien un joueur et si il a ete trouve
3. qui la map soit bien fernee
*/
int	validate_map(t_game *game)
{
	int		player_count;
	char	**map;
	char	c;

	int y, x;
	player_count = 0;
	map = game->map.grid;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (!ft_strchr("01NSEW ", c))
				return (exit_error("Error\nCaractère invalide dans la map"), 0);
			if (ft_strchr("NSEW", c))
			{
				if (player_count++)
					return (exit_error("Error\nPlus d’un joueur trouvé"), 0);
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
