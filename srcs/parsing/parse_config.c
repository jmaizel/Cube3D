/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:40:00 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:17:01 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Parse les textures de base (nord, sud, est, ouest) */
int	parse_config_textures(char **lines, t_game *game, int *i, int *config_count)
{
	if (ft_strncmp(lines[*i], "NO ", 3) == 0)
	{
		if (game->north_tex.img)
			return (exit_error("Error\nDuplication texture NO"), 0);
		game->north_tex.img = (void *)ft_strdup(lines[*i] + 3);
		(*config_count)++;
	}
	else if (ft_strncmp(lines[*i], "SO ", 3) == 0)
	{
		if (game->south_tex.img)
			return (exit_error("Error\nDuplication texture SO"), 0);
		game->south_tex.img = (void *)ft_strdup(lines[*i] + 3);
		(*config_count)++;
	}
	else if (ft_strncmp(lines[*i], "WE ", 3) == 0)
	{
		if (game->west_tex.img)
			return (exit_error("Error\nDuplication texture WE"), 0);
		game->west_tex.img = (void *)ft_strdup(lines[*i] + 3);
		(*config_count)++;
	}
	else if (ft_strncmp(lines[*i], "EA ", 3) == 0)
	{
		if (game->east_tex.img)
			return (exit_error("Error\nDuplication texture EA"), 0);
		game->east_tex.img = (void *)ft_strdup(lines[*i] + 3);
		(*config_count)++;
	}
	else
		return (1);
	return (2);
}

/* Parse les couleurs du sol et du plafond */
int	parse_config_colors(char **lines, t_game *game, int *i, int *config_count)
{
	if (ft_strncmp(lines[*i], "F ", 2) == 0)
	{
		if (game->floor_color != 0)
			return (exit_error("Error\nDuplication couleur F"), 0);
		game->floor_color = parse_color_line(lines[*i] + 2);
		if (game->floor_color == -1)
			return (0);
		(*config_count)++;
	}
	else if (ft_strncmp(lines[*i], "C ", 2) == 0)
	{
		if (game->ceiling_color != 0)
			return (exit_error("Error\nDuplication couleur C"), 0);
		game->ceiling_color = parse_color_line(lines[*i] + 2);
		if (game->ceiling_color == -1)
			return (0);
		(*config_count)++;
	}
	else
		return (1);
	return (2);
}

/* Parse les textures pour les portes */
int	parse_config_door(char **lines, t_game *game, int *i)
{
	if (ft_strncmp(lines[*i], "DR ", 3) == 0)
	{
		game->door_tex.img = (void *)ft_strdup(lines[*i] + 3);
		return (2);
	}
	return (1);
}

/* Parse les textures pour les armes */
int	parse_config_weapon(char **lines, t_game *game, int *i)
{
	if (ft_strncmp(lines[*i], "WP0 ", 4) == 0)
	{
		game->weapon_paths[0] = ft_strdup(lines[*i] + 4);
		game->weapon_frame_count = 1;
	}
	else if (ft_strncmp(lines[*i], "WP1 ", 4) == 0)
	{
		game->weapon_paths[1] = ft_strdup(lines[*i] + 4);
		if (game->weapon_frame_count < 2)
			game->weapon_frame_count = 2;
	}
	else if (ft_strncmp(lines[*i], "WP2 ", 4) == 0)
	{
		game->weapon_paths[2] = ft_strdup(lines[*i] + 4);
		if (game->weapon_frame_count < 3)
			game->weapon_frame_count = 3;
	}
	else if (ft_strncmp(lines[*i], "WP3 ", 4) == 0)
	{
		game->weapon_paths[3] = ft_strdup(lines[*i] + 4);
		if (game->weapon_frame_count < 4)
			game->weapon_frame_count = 4;
	}
	else
		return (1);
	return (2);
}

/* Parse les textures pour les monstres */
int	parse_config_monster(char **lines, t_game *game, int *i)
{
	if (ft_strncmp(lines[*i], "MT0 ", 4) == 0)
	{
		game->monster_paths[0] = ft_strdup(lines[*i] + 4);
		game->monster_frame_count = 1;
	}
	else if (ft_strncmp(lines[*i], "MT1 ", 4) == 0)
	{
		game->monster_paths[1] = ft_strdup(lines[*i] + 4);
		if (game->monster_frame_count < 2)
			game->monster_frame_count = 2;
	}
	else if (ft_strncmp(lines[*i], "MT2 ", 4) == 0)
	{
		game->monster_paths[2] = ft_strdup(lines[*i] + 4);
		if (game->monster_frame_count < 3)
			game->monster_frame_count = 3;
	}
	else if (ft_strncmp(lines[*i], "MT3 ", 4) == 0)
	{
		game->monster_paths[3] = ft_strdup(lines[*i] + 4);
		if (game->monster_frame_count < 4)
			game->monster_frame_count = 4;
	}
	else
		return (1);
	return (2);
}