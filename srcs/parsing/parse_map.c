/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:11:54 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/05/22 11:11:15 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static int	copy_map_lines(t_game *game, char **lines, int start_index,
		int map_lines)
{
	int	i;
	int	j;

	i = start_index;
	j = 0;
	while (j < map_lines && lines[i])
	{
		if (is_map_line(lines[i]))
		{
			game->map.grid[j] = ft_strdup(lines[i]);
			if (!game->map.grid[j])
			{
				while (--j >= 0)
					free(game->map.grid[j]);
				free(game->map.grid);
				game->map.grid = NULL;
				return (0);
			}
			j++;
		}
		i++;
	}
	game->map.grid[j] = NULL;
	return (1);
}

static int	build_map_structure(t_game *game, char **lines, int start_index,
		int map_lines)
{
	game->map.grid = malloc(sizeof(char *) * (map_lines + 1));
	if (!game->map.grid)
		return (0);
	if (!copy_map_lines(game, lines, start_index, map_lines))
		return (0);
	game->map.height = map_lines;
	game->map.width = find_max_width(game->map.grid);
	if (!validate_map(game))
		return (0);
	return (1);
}

int	parse_map(char **lines, t_game *game, int start_index)
{
	int	map_start;
	int	map_lines;

	map_start = 0;
	map_lines = count_map_lines(lines, start_index, &map_start);
	if (map_lines == 0)
		return (0);
	if (!build_map_structure(game, lines, map_start, map_lines))
	{
		if (game->map.grid)
			free_map(game->map.grid);
		return (0);
	}
	return (1);
}
