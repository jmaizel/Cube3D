/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:39:22 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/27 17:48:03 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Lit toutes les lignes d'un fichier et les retourne dans un tableau */
char **read_files_lines(const char *filename)
{
	int fd;
	char *line;
	char **lines;
	int count;
	int i;
	int len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		lines[i] = line;
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

/* Libère la mémoire d'un tableau de chaînes */
void free_split(char **split)
{
	int i;

	i = 0;
	if (!split)
		return;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/* Parse une ligne de couleur RGB et la convertit en un entier */
int parse_color_line(char *line)
{
	char **parts;
	int color;
	int r;
	int g;
	int b;

	parts = ft_split(line, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (exit_error("Error\nCouleur invalide"), -1);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (exit_error("Error\nValeurs RGB hors limites"), -1);
	color = (r << 16) | (g << 8) | b;
	free_split(parts);
	return (color);
}

/* Parse les lignes de configuration (textures et couleurs) du fichier .cub */
int parse_config(char **lines, t_game *game, int *map_start_index)
{
	int i;
	int config_count;
	int no_set;
	int so_set;
	int we_set;
	int ea_set;
	int f_set;
	int c_set;
	int j;

	config_count = 0;
	no_set = 0;
	so_set = 0;
	we_set = 0;
	ea_set = 0;
	f_set = 0;
	c_set = 0;
	i = 0;
	while (lines[i])
	{
		if (lines[i][0] == '\0')
		{
			i++;
			continue;
		}
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
		{
			if (no_set)
				return (exit_error("Error\nDuplication texture NO"), 0);
			game->north_tex.img = (void *)ft_strdup(lines[i] + 3);
			no_set = 1;
			config_count++;
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
		{
			if (so_set)
				return (exit_error("Error\nDuplication texture SO"), 0);
			game->south_tex.img = (void *)ft_strdup(lines[i] + 3);
			so_set = 1;
			config_count++;
		}
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
		{
			if (we_set)
				return (exit_error("Error\nDuplication texture WE"), 0);
			game->west_tex.img = (void *)ft_strdup(lines[i] + 3);
			we_set = 1;
			config_count++;
		}
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
		{
			if (ea_set)
				return (exit_error("Error\nDuplication texture EA"), 0);
			game->east_tex.img = (void *)ft_strdup(lines[i] + 3);
			ea_set = 1;
			config_count++;
		}
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
		{
			if (f_set)
				return (exit_error("Error\nDuplication couleur F"), 0);
			game->floor_color = parse_color_line(lines[i] + 2);
			if (game->floor_color == -1)
				return (0);
			f_set = 1;
			config_count++;
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
		{
			if (c_set)
				return (exit_error("Error\nDuplication couleur C"), 0);
			game->ceiling_color = parse_color_line(lines[i] + 2);
			if (game->ceiling_color == -1)
				return (0);
			c_set = 1;
			config_count++;
		}
		else if (ft_strncmp(lines[i], "SD ", 3) == 0)
		{
			game->special_door_path = ft_strdup(lines[i] + 3);
		}
		else if (ft_strncmp(lines[i], "WP0 ", 4) == 0)
		{
			game->weapon_paths[0] = ft_strdup(lines[i] + 4);
			game->weapon_frame_count = 1;
		}
		else if (ft_strncmp(lines[i], "WP1 ", 4) == 0)
		{
			game->weapon_paths[1] = ft_strdup(lines[i] + 4);
			if (game->weapon_frame_count < 2)
				game->weapon_frame_count = 2;
		}
		else if (ft_strncmp(lines[i], "WP2 ", 4) == 0)
		{
			game->weapon_paths[2] = ft_strdup(lines[i] + 4);
			if (game->weapon_frame_count < 3)
				game->weapon_frame_count = 3;
		}
		else if (ft_strncmp(lines[i], "WP3 ", 4) == 0)
		{
			game->weapon_paths[3] = ft_strdup(lines[i] + 4);
			if (game->weapon_frame_count < 4)
				game->weapon_frame_count = 4;
		}
		else if (ft_strncmp(lines[i], "MT0 ", 4) == 0)
		{
			game->monster_paths[0] = ft_strdup(lines[i] + 4);
			game->monster_frame_count = 1;
		}
		else if (ft_strncmp(lines[i], "MT1 ", 4) == 0)
		{
			game->monster_paths[1] = ft_strdup(lines[i] + 4);
			if (game->monster_frame_count < 2)
				game->monster_frame_count = 2;
		}
		else if (ft_strncmp(lines[i], "MT2 ", 4) == 0)
		{
			game->monster_paths[2] = ft_strdup(lines[i] + 4);
			if (game->monster_frame_count < 3)
				game->monster_frame_count = 3;
		}
		else if (ft_strncmp(lines[i], "MT3 ", 4) == 0)
		{
			game->monster_paths[3] = ft_strdup(lines[i] + 4);
			if (game->monster_frame_count < 4)
				game->monster_frame_count = 4;
		}
		else
		{
			j = 0;
			while (lines[i][j] && (lines[i][j] == ' ' || lines[i][j] == '\t'))
				j++;
			if (lines[i][j] && ft_strchr("01PNSEW", lines[i][j]))
			{
				if (config_count < 6)
					return (exit_error("Error\nConfiguration incomplète avant la map"),
							0);
				*map_start_index = i;
				break;
			}
			else
			{
				return (exit_error("Error\nLigne de config inconnue"), 0);
			}
		}
		i++;
	}
	if (config_count < 6)
		return (exit_error("Error\nConfiguration incomplète"), 0);
	return (1);
}

/* Parse le fichier .cub complet (configuration et map) */
int parse_cub_file(const char *filename, t_game *game)
{
	char **lines;
	int map_start_index;

	lines = read_files_lines(filename);
	if (!lines)
		return (exit_error("Error: Could not read .cub file"), 0);
	map_start_index = 0;
	if (!parse_config(lines, game, &map_start_index))
		return (free_split(lines), 0);
	if (!parse_map(lines, game, map_start_index))
		return (free_split(lines), 0);
	free_split(lines);
	return (1);
}