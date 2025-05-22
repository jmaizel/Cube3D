/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:24:07 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/22 14:08:36 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	check_content_after_map(char **lines, int end_index)
{
	int	i;

	i = end_index;
	while (lines[i])
	{
		if (lines[i][0] != '\0' && !is_empty_line(lines[i]))
			return (0);
		i++;
	}
	return (1);
}

int	count_map_lines(char **lines, int start_index, int *map_start)
{
	int	i;
	int	found_map;
	int	in_map;
	int	map_lines;

	i = start_index;
	found_map = 0;
	in_map = 0;
	map_lines = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]) && !found_map)
		{
			found_map = 1;
			*map_start = i;
		}
		if (!handle_map_line(lines, i, &in_map, &map_lines))
			break ;
		i++;
	}
	if (!check_content_after_map(lines, i) && lines[i])
		return (exit_error("Error\nInvalid content after map"), 0);
	if (map_lines == 0)
		return (exit_error("Error\nNo map found"), 0);
	return (map_lines);
}