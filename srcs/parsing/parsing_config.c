/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:07:23 by cdedessu          #+#    #+#             */
/*   Updated: 2025/06/02 11:49:03 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	process_colors(char *line, t_game *game, int *config_count,
		t_config_flags *flags)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!parse_color_config(line, &game->floor_color, &flags->f_set))
			return (-1);
		(*config_count)++;
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (!parse_color_config(line, &game->ceiling_color, &flags->c_set))
			return (-1);
		(*config_count)++;
		return (1);
	}
	return (0);
}

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

static int	check_map_begin(char *line, int *config_count,
		t_config_flags *flags)
{
	int	is_map;

	is_map = is_map_start(line);
	if (is_map)
	{
		if (!check_config_count(*config_count, 6,
				"Error\nIncomplete configuration before the map"))
			return (-1);
		if (!validate_required_configs(flags))
			return (-1);
		return (2);
	}
	return (handle_unknown_config(is_map));
}

static int	process_config_elements(char *trimmed_line, t_game *game,
		int *config_count, t_config_flags *flags)
{
	int	result;

	result = process_north_south(trimmed_line, game, config_count, flags);
	result = check_result(result);
	if (result != 0)
		return (result);
	result = process_west_east(trimmed_line, game, config_count, flags);
	result = check_result(result);
	if (result != 0)
		return (result);
	result = process_colors(trimmed_line, game, config_count, flags);
	result = check_result(result);
	if (result != 0)
		return (result);
	result = process_door_texture(trimmed_line, game, config_count);
	if (result != 0)
		return (result);
	result = process_weapon_textures(trimmed_line, game);
	if (result != 0)
		return (result);
	result = process_monster_textures(trimmed_line, game);
	return (result);
}

int	process_line(char *line, t_game *game, int *config_count,
		t_config_flags *flags)
{
	int		result;
	char	*trimmed_line;

	if (line[0] == '\0')
		return (1);
	trimmed_line = ft_skip_whitespace(line);
	if (trimmed_line[0] == '\0')
		return (1);
	result = process_config_elements(trimmed_line, game, config_count, flags);
	if (result != 0)
		return (result);
	return (check_map_begin(trimmed_line, config_count, flags));
}
