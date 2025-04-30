/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:41:00 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:28:30 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Vérifie si la ligne est le début d'une map */
int	check_if_map_start(char *line, int config_count, int *map_start_index, int i)
{
	int	j;

	j = 0;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && ft_strchr("01PNSEW", line[j]))
	{
		if (config_count < 6)
			return (exit_error("Error\nConfiguration incomplète avant la map"),
				0);
		*map_start_index = i;
		return (1);
	}
	return (2);
}

/* Traite une ligne de configuration */
int	process_config_line(char **lines, t_game *game, int *i, int *config_count, 
	int *map_start_index)
{
	int	result;

	result = parse_config_textures(lines, game, i, config_count);
	if (result != 1)
		return (result);
	result = parse_config_colors(lines, game, i, config_count);
	if (result != 1)
		return (result);
	result = parse_config_door(lines, game, i);
	if (result != 1)
		return (result);
	result = parse_config_weapon(lines, game, i);
	if (result != 1)
		return (2);
	result = parse_config_monster(lines, game, i);
	if (result != 1)
		return (2);
	return (check_if_map_start(lines[*i], *config_count, map_start_index, *i));
}

/* Parse les lignes de configuration du fichier .cub */
int	parse_config(char **lines, t_game *game, int *map_start_index)
{
	int	i;
	int	config_count;
	int	result;

	i = 0;
	config_count = 0;
	while (lines[i])
	{
		if (lines[i][0] == '\0')
		{
			i++;
			continue ;
		}
		result = process_config_line(lines, game, &i, &config_count, map_start_index);
		if (result == 0)
			return (0);
		else if (result == 1)
			break ;
		i++;
	}
	if (config_count < 6)
		return (exit_error("Error\nConfiguration incomplète"), 0);
	return (1);
}