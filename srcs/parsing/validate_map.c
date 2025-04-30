/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:12:10 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/04/30 18:46:53 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Vérifie si une case (0, N, S, E, W) est entourée par des murs ou des cases valides
 * 
 * @param map Tableau 2D représentant la map
 * @param y Coordonnée Y de la case
 * @param x Coordonnée X de la case
 * @param height Hauteur de la map
 * @return 1 si la case est fermée, 0 sinon
 */
static int	is_cell_enclosed(char **map, int y, int x, int height)
{
	int	start;
	int	end;
	int	line_len;

	if (y == 0 || y == height - 1)
		return (0);
	line_len = ft_strlen(map[y]);
	start = 0;
	end = line_len - 1;
	while (map[y][start] == ' ')
		start++;
	while (end > 0 && map[y][end] == ' ')
		end--;
	if (x == start || x == end)
		return (0);
	if (y > 0 && (x >= (int)ft_strlen(map[y - 1]) || map[y - 1][x] == ' '))
		return (0);
	if (y < height - 1 && (x >= (int)ft_strlen(map[y + 1]) || map[y + 1][x] == ' '))
		return (0);
	if (x > 0 && map[y][x - 1] == ' ')
		return (0);
	if (x < line_len - 1 && map[y][x + 1] == ' ')
		return (0);
	return (1);
}

/**
 * Vérifie si la map est fermée en contrôlant les espaces autour des zones jouables
 * 
 * @param map Tableau 2D représentant la map
 * @param width Largeur de la map
 * @param height Hauteur de la map
 * @return 1 si la map est fermée, 0 sinon
 */
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
				if (!is_cell_enclosed(map, y, x, height))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/**
 * Initialise la position et l'orientation du joueur selon la direction spécifiée
 * 
 * @param game Structure principale du jeu
 * @param x Coordonnée X du joueur
 * @param y Coordonnée Y du joueur
 * @param dir Direction du joueur (N, S, E, W)
 */
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

/**
 * Parcourt la map pour vérifier les caractères valides et trouver le joueur
 * 
 * @param game Structure principale du jeu
 * @param player_count Pointeur pour compter le nombre de joueurs trouvés
 * @return 1 si la map est valide, 0 sinon
 */
static int	check_map_characters(t_game *game, int *player_count)
{
	char	**map;
	char	c;
	int		y;
	int		x;

	map = game->map.grid;
	*player_count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (!ft_strchr("01PNSEWMD ", c))
				return (exit_error("Error\nCaractère invalide dans la map"), 0);
			if (ft_strchr("NSEW", c))
			{
				if ((*player_count)++)
					return (exit_error("Error\nPlus d'un joueur trouvé"), 0);
				init_player(game, x, y, c);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/**
 * Valide la map en vérifiant les caractères, le nombre de joueurs et si elle est fermée
 * 
 * @param game Structure principale du jeu
 * @return 1 si la map est valide, 0 sinon
 */
int	validate_map(t_game *game)
{
	int	player_count;

	if (!check_map_characters(game, &player_count))
		return (0);
	if (player_count != 1)
		return (exit_error("Error\nAucun joueur trouvé"), 0);
	if (!is_map_closed(game->map.grid, game->map.width, game->map.height))
		return (exit_error("Error\nMap non fermée"), 0);
	return (1);
}
