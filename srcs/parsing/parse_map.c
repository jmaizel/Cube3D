/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:11:54 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/04/30 18:38:44 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Trouve la largeur maximale dans un tableau de lignes de map
 *
 * @param map_lines Tableau de chaînes représentant les lignes de la map
 * @return La longueur de la ligne la plus longue
 */
int	find_max_width(char **map_lines)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map_lines[i])
	{
		len = ft_strlen(map_lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

/**
 * Vérifie si une ligne est une ligne de map valide
 *
 * @param line Ligne à vérifier
 * @return 1 si la ligne contient des caractères de map valides, 0 sinon
 */
static int	is_map_line(char *line)
{
	int	i;
	int	found_valid_char;

	i = 0;
	found_valid_char = 0;
	while (line[i])
	{
		if (ft_strchr("01PNSEWMD", line[i]))
			found_valid_char = 1;
		else if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (found_valid_char);
}

/**
 * Vérifie si une ligne vide interrompt la map
 *
 * @param lines Tableau de lignes du fichier
 * @param i Index de la ligne vide
 * @return 1 si la ligne vide est suivie d'une ligne de map, 0 sinon
 */
static int	is_map_interrupted(char **lines, int i)
{
	int	j;

	j = i + 1;
	while (lines[j])
	{
		if (is_map_line(lines[j]))
			return (1);
		j++;
	}
	return (0);
}

/**
 * Compte le nombre de lignes de la map et vérifie sa validité
 *
 * @param lines Tableau de lignes du fichier
 * @param start_index Index de départ pour la recherche
 * @param map_start Pointeur pour stocker l'index de début de la map
 * @return Nombre de lignes de la map, 0 si erreur
 */
static int	count_map_lines(char **lines, int start_index, int *map_start)
{
	int	i;
	int	found_map;
	int	in_map;
	int	map_lines;

	i = start_index;
	found_map = 0;
	in_map = 0;
	map_lines = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
		{
			if (!found_map)
			{
				found_map = 1;
				*map_start = i;
			}
			in_map = 1;
			map_lines++;
		}
		else if (lines[i][0] == '\0')
		{
			if (in_map && is_map_interrupted(lines, i))
				return (exit_error("Error\nLigne vide dans la map"), 0);
		}
		else
		{
			if (in_map)
				break ;
			else if (found_map)
				return (exit_error("Error\nLigne invalide dans la map"), 0);
		}
		i++;
	}
	if (map_lines == 0)
		return (exit_error("Error\nAucune map trouvée"), 0);
	return (map_lines);
}

/**
 * Alloue et remplit la structure de map à partir des lignes du fichier
 *
 * @param game Structure principale du jeu
 * @param lines Tableau de lignes du fichier
 * @param start_index Index de début de la map
 * @param map_lines Nombre de lignes de la map
 * @return 1 en cas de succès, 0 en cas d'erreur
 */
static int	build_map_structure(t_game *game, char **lines, int start_index,
		int map_lines)
{
	int	i;
	int	j;

	game->map.grid = malloc(sizeof(char *) * (map_lines + 1));
	if (!game->map.grid)
		return (0);
	i = start_index;
	j = 0;
	while (j < map_lines && lines[i])
	{
		if (is_map_line(lines[i]))
		{
			game->map.grid[j] = ft_strdup(lines[i]);
			j++;
		}
		i++;
	}
	game->map.grid[j] = NULL;
	game->map.height = map_lines;
	game->map.width = find_max_width(game->map.grid);
	if (!validate_map(game))
		return (0);
	return (1);
}

/**
 * Parse la map à partir des lignes du fichier
 *
 * @param lines Tableau de lignes du fichier
 * @param game Structure principale du jeu
 * @param start_index Index de départ pour la recherche
 * @return 1 en cas de succès, 0 en cas d'erreur
 */
int	parse_map(char **lines, t_game *game, int start_index)
{
	int	map_start;
	int	map_lines;

	map_start = 0;
	map_lines = count_map_lines(lines, start_index, &map_start);
	if (map_lines == 0)
		return (0);
	return (build_map_structure(game, lines, map_start, map_lines));
}
