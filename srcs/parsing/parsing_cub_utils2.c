/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:05:22 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/02 19:20:30 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Parse une ligne de configuration pour une frame d'arme
 */
int	parse_weapon_frame(t_game *game, char *line, int index)
{
	game->weapon_paths[index] = ft_strdup(line + 4);
	if (game->weapon_frame_count < index + 1)
		game->weapon_frame_count = index + 1;
	return (1);
}

/**
 * Parse une ligne de configuration pour une frame de monstre
 */
int	parse_monster_frame(t_game *game, char *line, int index)
{
	game->monster_paths[index] = ft_strdup(line + 4);
	if (game->monster_frame_count < index + 1)
		game->monster_frame_count = index + 1;
	return (1);
}

/**
 * Vérifie si une ligne est le début de la map
 */
int	is_map_start(char *line)
{
	int	j;

	j = 0;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && ft_strchr("01PNSEW", line[j]))
		return (1);
	return (0);
}

/**
 * Vérifie si le nombre d'éléments de configuration est suffisant
 */
int	check_config_count(int config_count, int min_required, char *error_msg)
{
	if (config_count < min_required)
		return (exit_error(error_msg), 0);
	return (1);
}

/**
 * Traite les erreurs de ligne de configuration inconnue
 */
int	handle_unknown_config(int is_map_start_flag)
{
	if (is_map_start_flag)
		return (1);
	return (exit_error("Error\nLigne de config inconnue"), -1);
}
