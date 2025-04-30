/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:11:54 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/04/30 16:17:47 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Trouve la largeur maximale dans un tableau de lignes de map */
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

/* Vérifie si une ligne est une ligne de map valide */
int	is_map_line(char *line)
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

/* Compte le nombre de lignes de map et vérifie qu'il n'y a pas de vide */
int	count_map_lines(char **lines, int start_index, int *map_start)
{
	int	i;
	int	map_lines;
	int	found_map;
	int	in_map;
	int	j;

	i = start_index;
	*map_start = -1;
	map_lines = 0;
	found_map = 0;
	in_map = 0;
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
			if (in_map)
			{
				j = i + 1;
				while (lines[j])
				{
					if (is_map_line(lines[j]))
						return (exit_error("Error\nLigne vide dans la map"), 0);
					j++;
				}
				break ;
			}
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

/* Copie les lignes de map dans game->map.grid */
int	process_map_lines(char **lines, t_game *game, int start, int map_lines)
{
	int	i;
	int	j;

	game->map.grid = malloc(sizeof(char *) * (map_lines + 1));
	if (!game->map.grid)
		return (0);
	i = start;
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

/* Parse la map à partir des lignes du fichier */
int	parse_map(char **lines, t_game *game, int start_index)
{
	int	map_lines;
	int	start;

	map_lines = count_map_lines(lines, start_index, &start);
	if (map_lines <= 0)
		return (0);
	if (!process_map_lines(lines, game, start, map_lines))
		return (0);
	return (1);
}