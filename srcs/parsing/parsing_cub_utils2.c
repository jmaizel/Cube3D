/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:05:22 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:54:42 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_weapon_frame(t_game *game, char *line, int index)
{
	if (game->weapon_paths[index] != NULL)
		return (exit_error("Error\nWeapon texture duplication"), 0);
	game->weapon_paths[index] = ft_strdup(line + 4);
	if (game->weapon_frame_count < index + 1)
		game->weapon_frame_count = index + 1;
	return (1);
}

int	parse_monster_frame(t_game *game, char *line, int index)
{
	if (game->monster_paths[index] != NULL)
		return (exit_error("Error\nMonster Texture Duplication"), 0);
	game->monster_paths[index] = ft_strdup(line + 4);
	if (game->monster_frame_count < index + 1)
		game->monster_frame_count = index + 1;
	return (1);
}

int	is_map_start(char *line)
{
	int	j;

	j = 0;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (ft_strncmp(line + j, "NO ", 3) == 0 || ft_strncmp(line + j, "SO ",
			3) == 0 || ft_strncmp(line + j, "WE ", 3) == 0 || ft_strncmp(line
			+ j, "EA ", 3) == 0 || ft_strncmp(line + j, "F ", 2) == 0
		|| ft_strncmp(line + j, "C ", 2) == 0 || ft_strncmp(line + j, "DR ",
			3) == 0 || ft_strncmp(line + j, "MT", 2) == 0 || ft_strncmp(line
			+ j, "WP", 2) == 0)
		return (0);
	if (line[j] && ft_strchr("01NSEWDM", line[j]))
		return (1);
	return (0);
}

int	check_config_count(int config_count, int min_required, char *error_msg)
{
	if (config_count < min_required)
		return (exit_error(error_msg), 0);
	return (1);
}

int	handle_unknown_config(int is_map_start_flag)
{
	if (is_map_start_flag)
		return (1);
	return (exit_error("Error\nUnknown configuration line"), -1);
}
