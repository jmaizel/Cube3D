/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:13:10 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/04/30 15:45:12 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Parcourt la map pour compter et initialiser les joueurs */
int	count_players(t_game *game, char **map)
{
	int		y;
	int		x;
	int		player_count;
	char	c;

	player_count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
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
	return (player_count);
}

/* Valide la map en vérifiant les caractères,
	le nombre de joueurs et si elle est fermée */
int	validate_map(t_game *game)
{
	int		y;
	int		x;
	char	c;
	char	**map;

	map = game->map.grid;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (!ft_strchr("01PNSEWMD ", c))
				return (exit_error("Error\nCaractère invalide dans la map"), 0);
			x++;
		}
		y++;
	}
	if (count_players(game, map) != 1)
		return (exit_error("Error\nNombre de joueurs incorrect"), 0);
	if (!is_map_closed(game->map.grid, game->map.width, game->map.height))
		return (exit_error("Error\nMap non fermée"), 0);
	return (1);
}