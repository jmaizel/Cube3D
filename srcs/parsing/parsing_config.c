/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:07:23 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/05 15:07:02 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Traite les couleurs (F, C)
 */
static int	process_colors(char *line, t_game *game, int *config_count,
		t_config_flags *flags)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!parse_color_config(line, &game->floor_color, &flags->f_set))
			return (0);
		(*config_count)++;
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (!parse_color_config(line, &game->ceiling_color, &flags->c_set))
			return (0);
		(*config_count)++;
		return (1);
	}
	return (0);
}

/**
 * Traite les textures supplémentaires (porte)
 */
static int	process_door_texture(char *line, t_game *game, int *config_count)
{
	if (ft_strncmp(line, "DR ", 3) == 0)
	{
		game->door_tex.img = (void *)ft_strdup(line + 3);
		(*config_count)++;
		return (1);
	}
	return (0);
}

/**
 * Traite la ligne de configuration pour vérifier s'il s'agit du début de la map
 */
static int	check_map_begin(char *line, int *config_count)
{
	int	is_map;

	is_map = is_map_start(line);
	if (is_map)
	{
		if (!check_config_count(*config_count, 6,
				"Error\nConfiguration incomplète avant la map"))
			return (-1);
		return (2);
	}
	return (handle_unknown_config(is_map));
}

/**
 * Traite une ligne de configuration
 */
int	process_line(char *line, t_game *game, int *config_count,
		t_config_flags *flags)
{
	int	result;

	if (line[0] == '\0')
		return (1);
	result = process_north_south(line, game, config_count, flags);
	if (result != 0)
		return (result);
	result = process_west_east(line, game, config_count, flags);
	if (result != 0)
		return (result);
	result = process_colors(line, game, config_count, flags);
	if (result != 0)
		return (result);
	result = process_door_texture(line, game, config_count);
	if (result != 0)
		return (result);
	result = process_weapon_textures(line, game);
	if (result != 0)
		return (result);
	result = process_monster_textures(line, game);
	if (result != 0)
		return (result);
	return (check_map_begin(line, config_count));
}

/**
 * Vérifie si une ligne est une texture
 */
int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "DR ", 3) == 0 || ft_strncmp(line, "MT", 2) == 0
		|| ft_strncmp(line, "WP", 2) == 0);
}
