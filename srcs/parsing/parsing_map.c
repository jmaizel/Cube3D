/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:11:54 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/04/01 11:53:35 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
en gros cette fonction permet de voir quel est la ligne la plus grande,
car conctrerement a so_long les lignes peuvent avoir des longueur differents
exemple :
111111
1001
100001
11111

est une map valide
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
/*
ok la on passe dans le parsing de la map	uniquement(pas que le .cub)
1. on cherche la premiere ligne de la map qui commence par 01NSEW forcement
2. on compte combien de ligne fait la map pour pouvoir l alouer apres et faire une copie
3. ensuite on appelle les fonctions de parsing avec validat_map
*/
int	parse_map(char **lines, t_game *game, int start_index)
{
	int	i;
	int	start;
	int	map_lines;

	i = start_index; // Commencer à partir de l'index spécifié
	start = i;
	map_lines = 0;
	while (lines[i] && ft_strchr(" 01NSEW", lines[i][0]))
	{
		map_lines++;
		i++;
	}
	game->map.grid = malloc(sizeof(char *) * (map_lines + 1));
	if (!game->map.grid)
		return (0);
	i = 0;
	while (i < map_lines)
	{
		game->map.grid[i] = ft_strdup(lines[start + i]);
		i++;
	}
	game->map.grid[i] = NULL;
	game->map.height = map_lines;
	game->map.width = find_max_width(game->map.grid);
	if (!validate_map(game))
		return (0);
	return (1);
}
