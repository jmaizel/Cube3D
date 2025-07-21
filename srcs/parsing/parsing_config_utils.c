/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:51:42 by cdedessu          #+#    #+#             */
/*   Updated: 2025/06/02 11:42:00 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	process_north_south(char *line, t_game *game, int *config_count,
		t_config_flags *flags)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (!parse_texture_line(line, &game->north_tex.img, &flags->no_set))
			return (-1);
		(*config_count)++;
		return (1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (!parse_texture_line(line, &game->south_tex.img, &flags->so_set))
			return (-1);
		(*config_count)++;
		return (1);
	}
	return (0);
}

int	process_west_east(char *line, t_game *game, int *config_count,
		t_config_flags *flags)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (!parse_texture_line(line, &game->west_tex.img, &flags->we_set))
			return (-1);
		(*config_count)++;
		return (1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (!parse_texture_line(line, &game->east_tex.img, &flags->ea_set))
			return (-1);
		(*config_count)++;
		return (1);
	}
	return (0);
}

int	process_weapon_textures(char *line, t_game *game)
{
	if (ft_strncmp(line, "WP0 ", 4) == 0)
		return (parse_weapon_frame(game, line, 0));
	else if (ft_strncmp(line, "WP1 ", 4) == 0)
		return (parse_weapon_frame(game, line, 1));
	else if (ft_strncmp(line, "WP2 ", 4) == 0)
		return (parse_weapon_frame(game, line, 2));
	else if (ft_strncmp(line, "WP3 ", 4) == 0)
		return (parse_weapon_frame(game, line, 3));
	return (0);
}

int	process_monster_textures(char *line, t_game *game)
{
	if (ft_strncmp(line, "MT0 ", 4) == 0)
		return (parse_monster_frame(game, line, 0));
	else if (ft_strncmp(line, "MT1 ", 4) == 0)
		return (parse_monster_frame(game, line, 1));
	else if (ft_strncmp(line, "MT2 ", 4) == 0)
		return (parse_monster_frame(game, line, 2));
	else if (ft_strncmp(line, "MT3 ", 4) == 0)
		return (parse_monster_frame(game, line, 3));
	return (0);
}
