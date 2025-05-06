/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:39:22 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/06 11:43:06 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Lit le contenu d'un fichier et le découpe en lignes
 */
char	**read_files_lines(const char *filename)
{
	int		fd;
	char	**lines;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	count = count_file_lines(fd);
	if (count <= 0)
		return (NULL);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = allocate_lines(fd, count);
	close(fd);
	return (lines);
}

/**
 * Libère la mémoire d'un tableau de chaînes
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
 * Parse le fichier .cub complet (configuration et map)
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
	{
		cleanup_config_resources(game);
		free_split(lines);
		return (0);
	}
	if (!parse_map(lines, game, map_start_index))
	{
		cleanup_config_resources(game);
		free_split(lines);
		return (0);
	}
	free_split(lines);
	return (1);
}
