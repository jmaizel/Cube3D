/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:39:22 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:16:45 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Lit toutes les lignes d'un fichier et les retourne dans un tableau */
char	**read_files_lines(const char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;
	int		i;

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
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		lines[i++] = line;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

/* Libère la mémoire d'un tableau de chaînes */
void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/* Parse une ligne de couleur RGB et la convertit en un entier */
int	parse_color_line(char *line)
{
	char	**parts;
	int		color;
	int		r;
	int		g;
	int		b;

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

/* Parse le fichier .cub complet (configuration et map) */
int	parse_cub_file(const char *filename, t_game *game)
{
	char	**lines;
	int		map_start_index;

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
