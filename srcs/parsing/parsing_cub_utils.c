/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:01:16 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/06 11:43:11 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Compte le nombre de lignes dans un fichier
 */
int	count_file_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	return (count);
}

/**
 * Alloue et remplit le tableau de lignes à partir du fichier
 */
char	**allocate_lines(int fd, int count)
{
	char	**lines;
	char	*line;
	int		i;
	int		len;

	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	i = 0;
	while (i < count)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		lines[i] = line;
		i++;
	}
	lines[i] = NULL;
	return (lines);
}

/**
 * Vérifie si une texture est déjà définie
 */
int	check_texture_duplication(int is_set, char *texture_type)
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
 */
int	parse_texture_line(char *line, void **texture_img, int *is_set)
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
 */
int	parse_color_config(char *line, int *color_ptr, int *is_set)
{
	if (!check_texture_duplication(*is_set, line))
		return (0);
	*color_ptr = parse_color_line(line + 2);
	if (*color_ptr == -1)
		return (0);
	*is_set = 1;
	return (1);
}
