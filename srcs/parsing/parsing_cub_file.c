/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:39:22 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/09 16:03:56 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
en gros ce que je fais dans cette fonctione :
- j essaye d ouvrir le fichier .cub et si ca echoue e renvoie null
- je concatene chaque lignes lue avec ft_join , qu on rajoute a joined
-  je free mis ligne et ma variable temporaire apres utilisation
- et apres on decoupe chaque lignes avec ft_split
*/
char	**read_files_lines(const char *filename)
{
	int		fd;
	char	*line;
	char	*joined;
	char	*tmp;
	char	**lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	joined = ft_calloc(1, 1);
	if (!joined)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		tmp = joined;
		joined = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		if (!joined)
			return (NULL);
	}
	close(fd);
	lines = ft_split(joined, '\n');
	free(joined);
	return (lines);
}

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

/*
fonction pour parser la couleur, en gros je repere ma ligne ,
	ou je traite une couleur
je la split a ;
een gros ,
	le but c est de convertir une couleur exprimee en RGB comme "200,100,0"
en un int que je vais pouvoir renvoyer a la mlx pour qu il fasse ne couleur
je te montrerai avec une exemple

*/
int	parse_color_line(char *line)
{
	char	**parts;
	int		color;

	int r, g, b;
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

/*
alors dans cette fonction zeubi , le but c est de parser le .CUb
 - je vais commencer par skip les espaces
 - si je tomber sur une ligne de map , je m arrrete
 - je definie les textures et les couleurs
*/
int	parse_config(char **lines, t_game *game, int *map_start_index)
{
	int	i;
	int	config_count;

	config_count = 0;
	i = 0;
	while (lines[i])
	{
		if (lines[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
		{
			game->north_tex.img = (void *)ft_strdup(lines[i] + 3);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
		{
			game->south_tex.img = (void *)ft_strdup(lines[i] + 3);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
		{
			game->west_tex.img = (void *)ft_strdup(lines[i] + 3);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
		{
			game->east_tex.img = (void *)ft_strdup(lines[i] + 3);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
		{
			game->floor_color = parse_color_line(lines[i] + 2);
			if (game->floor_color == -1)
				return (0);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
		{
			game->ceiling_color = parse_color_line(lines[i] + 2);
			if (game->ceiling_color == -1)
				return (0);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "PO ", 3) == 0)
		{
			game->door_path = ft_strdup(lines[i] + 3);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "WP ", 3) == 0)
		{
			game->weapon_path = ft_strdup(lines[i] + 3);
			config_count++;
		}
		else if (ft_strchr("01NSEW", lines[i][0]))
		{
			*map_start_index = i;
			break ;
		}
		else
		{
			printf("  -> Ligne de config inconnue\n");
			return (exit_error("Error\nLigne de config inconnue"), 0);
		}
		i++;
	}
	if (config_count < 6)
		return (exit_error("Error\nConfiguration incomplète"), 0);
	return (1);
}

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
