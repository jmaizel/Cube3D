/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:39:22 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 18:48:46 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:39:22 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/01 15:50:20 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Lit le contenu d'un fichier et le découpe en lignes
 *
 * @param filename Nom du fichier à lire
 * @return Tableau de chaînes représentant les lignes du fichier, NULL si erreur
 */
char	**read_files_lines(const char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;
	int		i;
	int		len;

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
		lines[i++] = line;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

/**
 * Libère la mémoire d'un tableau de chaînes
 *
 * @param split Tableau de chaînes à libérer
 */
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

/**
 * Parse une ligne de couleur au format R,G,B
 *
 * @param line Ligne contenant les valeurs RGB
 * @return Couleur au format int, -1 si erreur
 */
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

/**
 * Vérifie si une texture est déjà définie
 *
 * @param is_set Indicateur si la texture est déjà définie
 * @param texture_type Type de texture (pour le message d'erreur)
 * @return 0 si la texture est déjà définie (erreur), 1 sinon
 */
static int	check_texture_duplication(int is_set, char *texture_type)
{
	if (is_set)
	{
		exit_error("Error\nDuplication texture ");
		ft_printf("%s\n", texture_type);
		return (0);
	}
	return (1);
}

/**
 * Parse une ligne de configuration pour une texture
 *
 * @param line Ligne de configuration
 * @param texture_img Pointeur pour stocker le chemin de la texture
 * @param is_set Indicateur si la texture est déjà définie
 * @return 1 si la texture a été ajoutée avec succès, 0 si erreur
 */
static int	parse_texture_line(char *line, void **texture_img, int *is_set)
{
	char	*texture_path;

	if (!check_texture_duplication(*is_set, line))
		return (0);
	texture_path = ft_strdup(line + 3);
	if (!texture_path)
		return (exit_error("Error\nMémoire insuffisante"), 0);
	*texture_img = (void *)texture_path;
	*is_set = 1;
	return (1);
}

/**
 * Parse une ligne de configuration pour une couleur
 *
 * @param line Ligne de configuration
 * @param color_ptr Pointeur pour stocker la couleur
 * @param is_set Indicateur si la couleur est déjà définie
 * @return 1 si la couleur a été ajoutée avec succès, 0 si erreur
 */
static int	parse_color_config(char *line, int *color_ptr, int *is_set)
{
	if (!check_texture_duplication(*is_set, line))
		return (0);
	*color_ptr = parse_color_line(line + 2);
	if (*color_ptr == -1)
		return (0);
	*is_set = 1;
	return (1);
}

/**
 * Parse une ligne de configuration pour une frame d'arme
 *
 * @param game Structure principale du jeu
 * @param line Ligne de configuration
 * @param index Index de la frame
 * @return 1 (toujours réussi)
 */
static int	parse_weapon_frame(t_game *game, char *line, int index)
{
	game->weapon_paths[index] = ft_strdup(line + 4);
	if (game->weapon_frame_count < index + 1)
		game->weapon_frame_count = index + 1;
	return (1);
}

/**
 * Parse une ligne de configuration pour une frame de monstre
 *
 * @param game Structure principale du jeu
 * @param line Ligne de configuration
 * @param index Index de la frame
 * @return 1 (toujours réussi)
 */
static int	parse_monster_frame(t_game *game, char *line, int index)
{
	game->monster_paths[index] = ft_strdup(line + 4);
	if (game->monster_frame_count < index + 1)
		game->monster_frame_count = index + 1;
	return (1);
}

/**
 * Vérifie si une ligne est le début de la map
 *
 * @param line Ligne à vérifier
 * @return 1 si la ligne semble être le début de la map, 0 sinon
 */
static int	is_map_start(char *line)
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
 *
 * @param config_count Nombre d'éléments de configuration trouvés
 * @param min_required Nombre minimum d'éléments requis
 * @param error_msg Message d'erreur à afficher si insuffisant
 * @return 1 si suffisant, 0 sinon
 */
static int	check_config_count(int config_count, int min_required, char *error_msg)
{
	if (config_count < min_required)
		return (exit_error(error_msg), 0);
	return (1);
}

/**
 * Parse les configurations du fichier .cub
 *
 * @param lines Tableau de lignes du fichier
 * @param game Structure principale du jeu
 * @param map_start_index Pointeur pour stocker l'index de début de la map
 * @return 1 en cas de succès, 0 en cas d'erreur
 */
int	parse_config(char **lines, t_game *game, int *map_start_index)
{
	int		i;
	int		config_count;
	int		no_set;
	int		so_set;
	int		we_set;
	int		ea_set;
	int		f_set;
	int		c_set;

	i = 0;
	config_count = 0;
	no_set = 0;
	so_set = 0;
	we_set = 0;
	ea_set = 0;
	f_set = 0;
	c_set = 0;
	while (lines[i])
	{
		if (lines[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
		{
			if (!parse_texture_line(lines[i], &game->north_tex.img, &no_set))
				return (0);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
		{
			if (!parse_texture_line(lines[i], &game->south_tex.img, &so_set))
				return (0);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
		{
			if (!parse_texture_line(lines[i], &game->west_tex.img, &we_set))
				return (0);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
		{
			if (!parse_texture_line(lines[i], &game->east_tex.img, &ea_set))
				return (0);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
		{
			if (!parse_color_config(lines[i], &game->floor_color, &f_set))
				return (0);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
		{
			if (!parse_color_config(lines[i], &game->ceiling_color, &c_set))
				return (0);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "DR ", 3) == 0)
		{
			game->door_tex.img = (void *)ft_strdup(lines[i] + 3);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "WP0 ", 4) == 0)
			parse_weapon_frame(game, lines[i], 0);
		else if (ft_strncmp(lines[i], "WP1 ", 4) == 0)
			parse_weapon_frame(game, lines[i], 1);
		else if (ft_strncmp(lines[i], "WP2 ", 4) == 0)
			parse_weapon_frame(game, lines[i], 2);
		else if (ft_strncmp(lines[i], "WP3 ", 4) == 0)
			parse_weapon_frame(game, lines[i], 3);
		else if (ft_strncmp(lines[i], "MT0 ", 4) == 0)
			parse_monster_frame(game, lines[i], 0);
		else if (ft_strncmp(lines[i], "MT1 ", 4) == 0)
			parse_monster_frame(game, lines[i], 1);
		else if (ft_strncmp(lines[i], "MT2 ", 4) == 0)
			parse_monster_frame(game, lines[i], 2);
		else if (ft_strncmp(lines[i], "MT3 ", 4) == 0)
			parse_monster_frame(game, lines[i], 3);
		else if (is_map_start(lines[i]))
		{
			if (!check_config_count(config_count, 6, 
					"Error\nConfiguration incomplète avant la map"))
				return (0);
			*map_start_index = i;
			break ;
		}
		else
			return (exit_error("Error\nLigne de config inconnue"), 0);
		i++;
	}
	return (check_config_count(config_count, 6, "Error\nConfiguration incomplète"));
}

/**
 * Parse le fichier .cub complet (configuration et map)
 *
 * @param filename Nom du fichier à analyser
 * @param game Structure principale du jeu
 * @return 1 en cas de succès, 0 en cas d'erreur
 */
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
